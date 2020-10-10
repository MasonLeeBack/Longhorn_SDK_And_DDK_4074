using System;
using System.Collaboration;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Data;
using System.Net;
using System.Text;
using System.Windows.Forms;

using Microsoft.Collaboration;
using Microsoft.Collaboration.Activity;

namespace RtcClient {

    /// <summary>
    /// Conversation context that can be used to identify our custom IM session
    /// </summary>

    [Serializable]
    public class InstantMessagingActivityConversationContext : ConversationContext {

        /// <summary>
        /// Default constructor for serialization.
        /// </summary>

        public InstantMessagingActivityConversationContext () {}

        /// <summary>
        /// Initializes the class with the conversation ID.
        /// </summary>
        /// <param name="conversationID">Conversation ID</param>

        public InstantMessagingActivityConversationContext (string conversationID) :
            base (conversationID) {}
    }

    //
    // Classes inherited from EventArgs for custom events.
    //

    /// <summary>
    /// Provides a container to transport IAsyncResult object to an event handler.
    /// </summary>

    public class AsyncEventArgs : UnhandledExceptionEventArgs {

        private IAsyncResult asyncResult;

        /// <summary>
        /// Initializes a new instance of the AsyncEventArgs class with
        /// the exception object and async result object.
        /// </summary>
        /// <param name="exception">The exception that is not handled</param>
        /// <param name="asyncResult">Async result object</param>

        public AsyncEventArgs (object exception, IAsyncResult asyncResult) :
            base (exception, false) {
            this.asyncResult = asyncResult;
        }

        /// <summary>
        /// Async result object. Read-only property.
        /// </summary>

        public IAsyncResult AsyncResultObject {
            get {
                return asyncResult;
            }
        }
    }

    /// <summary>
    /// Provides a container to transport status collection to an event handler.
    /// </summary>

    public class SendMessageSucceededEventArgs : EventArgs {

        private ICollection statusCollection;

        /// <summary>
        /// Initializes a new instance of the SendMessageSucceededEventArgs class with
        /// the status collection.
        /// </summary>        
        /// <param name="statusCollection">Status collection</param>

        public SendMessageSucceededEventArgs (ICollection statusCollection) :
            base () {
            this.statusCollection = statusCollection;
        }
        
        /// <summary>
        /// Async result object. Read-only property.
        /// </summary>

        public ICollection StatusCollection {
            get {
                return statusCollection;
            }
        }
    }

    //
    // Delegates.
    //

    [Serializable]
    public delegate void SendMessageSucceededEventHandler (
        object sender, 
        SendMessageSucceededEventArgs e
    );

    /// <summary>
    /// RealTimeProfile class represents real-time profile and provides
    /// functionality to perform log on and log off.
    /// </summary>

    public class RealTimeProfile : Component {

        //
        // Private properties.
        //

        private System.ComponentModel.Container components = null;

        //
        // Log on credentials.
        //

        private string userName;
        private string domain;
        private string password;
        private string realTimeAddress;

        internal RtcProvider provider;
        internal RtcProfile profile;

        internal InstantMessaging im;
        private ContactList contactList;

        /// <summary>
        /// Initializes an instance of the class.
        /// </summary>

        public RealTimeProfile () {
            InitializeComponent ();
            provider = new RtcProvider ();
        }

        /// <summary>
        /// Logs on with current credentials.
        /// </summary>

        public void LogOn () {

            RtcProfileConfiguration profileConfiguration;
            NetworkCredential networkCredential;

            //
            // Create network credential.
            //

            networkCredential = new NetworkCredential (UserName, Password, null);

            //
            // Create profile configuration.
            //

            profileConfiguration = new RtcProfileConfiguration ();
            profileConfiguration.Servers.Add (new RtcRealTimeServer (Domain, RtcRealTimeServer.RoleLogInServer));

            if (networkCredential.UserName.CompareTo ("") == 0) {
                profileConfiguration.AuthenticationProtocols = AuthenticationProtocols.Ntlm | AuthenticationProtocols.Kerberos;
                profileConfiguration.Transport = Microsoft.Collaboration.TransportType.Tls;
            }

            //
            // Create real-time profile.
            //

            if (profile != null) {

                if (profile.LogOnState == LogOnState.LoggedOn) {
                    profile.LogOff ();
                }

                provider.RemoveRealTimeProfile (profile);
                profile = null;
            }

            profile = provider.CreateRealTimeProfile (realTimeAddress, networkCredential, profileConfiguration);

            profile.LogOnStateChanged += new LogOnStateChangedEventHandler (OnLogOnStateChanged);

            if (profile.Signaling != null) {            
                profile.Signaling.SessionReceived += new IncomingSessionEventHandler (OnSessionReceived);
            }           

            RegisterContactListEventHandlers ();

            profile.LogOn ();
        }

        /// <summary>
        /// Logs off from the server.
        /// </summary>

        public void LogOff () {

            if (profile != null) {

                if (profile.LogOnState == LogOnState.LoggedOn) {
                    profile.LogOff ();
                }

                UnregisterContactListEventHandlers ();

                provider.RemoveRealTimeProfile (profile);
                profile = null;
            }
        }

        internal ContactList ContactList {
            get {
                return contactList;
            }
            set {
                UnregisterContactListEventHandlers ();
                contactList = value;
                RegisterContactListEventHandlers ();                
            }
        }

        private void RegisterContactListEventHandlers () {
            
            if (contactList != null && profile != null && profile.Presence != null && profile.PersistedData != null) {

                ProfilePresence pr = profile.Presence;
                ProfilePersistedData pd = profile.PersistedData;
                
                pr.PresenceSubscriptions.ItemAdded += new CollectionEventHandler (contactList.OnSubscriptionAdded);
                pr.PresenceSubscriptions.ItemRemoved += new CollectionEventHandler (contactList.OnSubscriptionRemoved);
                
                pd.ContactsSubscription.Contacts.ItemAdded += new CollectionEventHandler (contactList.OnContactAdded);
                pd.ContactsSubscription.Contacts.ItemRemoved += new CollectionEventHandler (contactList.OnContactRemoved);
            
                pd.ContactGroupsSubscription.ContactGroups.ItemAdded += new CollectionEventHandler (contactList.OnGroupAdded);
                pd.ContactGroupsSubscription.ContactGroups.ItemRemoved += new CollectionEventHandler (contactList.OnGroupRemoved);
            
                pd.AccessRulesSubscription.AccessRules.ItemAdded += new CollectionEventHandler (contactList.OnRuleAdded);
                pd.AccessRulesSubscription.AccessRules.ItemRemoved += new CollectionEventHandler (contactList.OnRuleRemoved);
            }            
        }

        private void UnregisterContactListEventHandlers () {
            
            if (contactList != null && profile != null && profile.Presence != null && profile.PersistedData != null) {

                ProfilePresence pr = profile.Presence;
                ProfilePersistedData pd = profile.PersistedData;
                
                pr.PresenceSubscriptions.ItemAdded -= new CollectionEventHandler (contactList.OnSubscriptionAdded);
                pr.PresenceSubscriptions.ItemRemoved -= new CollectionEventHandler (contactList.OnSubscriptionRemoved);
                
                pd.ContactsSubscription.Contacts.ItemAdded -= new CollectionEventHandler (contactList.OnContactAdded);
                pd.ContactsSubscription.Contacts.ItemRemoved -= new CollectionEventHandler (contactList.OnContactRemoved);
            
                pd.ContactGroupsSubscription.ContactGroups.ItemAdded -= new CollectionEventHandler (contactList.OnGroupAdded);
                pd.ContactGroupsSubscription.ContactGroups.ItemRemoved -= new CollectionEventHandler (contactList.OnGroupRemoved);
            
                pd.AccessRulesSubscription.AccessRules.ItemAdded -= new CollectionEventHandler (contactList.OnRuleAdded);
                pd.AccessRulesSubscription.AccessRules.ItemRemoved -= new CollectionEventHandler (contactList.OnRuleRemoved);
            }
        }

        /// <summary>
        /// Callback to be called when log on state changes.
        /// </summary>

        private void OnLogOnStateChanged (object sender, LogOnStateChangedEventArgs e) {

            if (e.IsErrorEvent) {
                LogOnFailed (this, new UnhandledExceptionEventArgs (e.GetException (), false));
            }
            else if ((sender as RtcProfile).LogOnState == LogOnState.LoggedOn) {
                LogOnSucceeded (this, EventArgs.Empty);
            }
            else if ((sender as RtcProfile).LogOnState == LogOnState.NotLoggedOn) {
                LogOffSucceeded (this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// Called when session received event gets raised.
        /// </summary>

        private void OnSessionReceived (object sender, IncomingSessionEventArgs e) {

            if (im != null && im.Session == null) {
                im.OnSessionReceived (sender, e);
            }
            else {
                SessionReceived (e.Session, e);
            }
        }        

        /// <summary>
        /// Cleans up any resources being used.
        /// </summary>

        protected override void Dispose (bool disposing) {
            if (disposing) {
                if (components != null) {
                    components.Dispose ();
                }
            }
            base.Dispose (disposing);
        }

        //
        // Run-time only properties.
        //

        /// <summary>
        /// RTC provider object from the underlying API. Read-only property.
        /// </summary>

        [Browsable (false)]
        public RtcProvider Provider {
            get {
                return provider;
            }
        }

        /// <summary>
        /// RTC profile object from the underlying API. Read-only property.
        /// </summary>

        [Browsable (false)]
        public RtcProfile Profile {
            get {
                return profile;
            }
        }

        //
        // Run-time and design-time properties.
        //

        /// <summary>
        /// User name to logon to the SIP server.
        /// </summary>

        [Category ("Logon credentials")]
        [Description ("User name to logon to the SIP server")]
        public string UserName {
            get {
                return userName;
            }
            set {
                userName = value;
            }
        }

        /// <summary>
        /// Domain name to logon to the SIP server.
        /// </summary>

        [Category ("Logon credentials")]
        [Description ("Domain name to logon to the SIP server")]
        public string Domain {
            get {
                return domain;
            }
            set {
                domain = value;
            }
        }

        /// <summary>
        /// User password to logon to the SIP server.
        /// </summary>

        [Category ("Logon credentials")]
        [Description ("User password to logon to the SIP server")]
        public string Password {
            get {
                return password;
            }
            set {
                password = value;
            }
        }

        /// <summary>
        /// SIP address of the user.
        /// </summary>

        [Category ("Logon credentials")]
        [Description ("Real-time address of the user")]
        public string RealTimeAddress {
            get {
                return realTimeAddress;
            }
            set {
                realTimeAddress = value;
            }
        }

        //
        // Events.
        //

        /// <summary>
        /// Occurs when log on succeeds.
        /// </summary>

        [Category ("Logging on/off")]
        [Description ("Occurs when log on succeeds")]
        public event EventHandler LogOnSucceeded;

        /// <summary>
        /// Occurs when log on fails.
        /// </summary>

        [Category ("Logging on/off")]
        [Description ("Occurs when log on fails")]
        public event UnhandledExceptionEventHandler LogOnFailed;

        /// <summary>
        /// Occurs when log off succeeds.
        /// </summary>

        [Category ("Logging on/off")]
        [Description ("Occurs when log off succeeds")]
        public event EventHandler LogOffSucceeded;

        /// <summary>
        /// Occurs when new session is received and there is no one to handle it
        /// (InstantMessaging object is not associated with this profile or it is
        /// busy in existing session).
        /// </summary>

        [Category ("Other events")]
        [Description ("Occurs when new session is received")]
        public event IncomingSessionEventHandler SessionReceived;

        #region Component Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent () {

        }
        #endregion
    }

    /// <summary>
    /// InstantMessaging class supports multi-party IM sessions.
    /// </summary>

    public class InstantMessaging : Component {

        //
        // Private properties.
        //

        private System.ComponentModel.Container components = null;

        internal RealTimeProfile realTimeProfile;

        private SignalingSession session;
        private InstantMessagingActivity activity;

        private AsyncCallback inviteCallback;
        private AsyncCallback sendMessageCallback;
        private AsyncCallback acceptCallback;

        private TextBoxBase messageBox;
        private TextBoxBase messageHistoryBox;
        private Button sendButton;        

        private Timer typingTimer;

        /// <summary>
        /// Initializes an instance of the class.
        /// </summary>

        public InstantMessaging () {

            InitializeComponent ();

            typingTimer = new System.Windows.Forms.Timer ();
            typingTimer.Tick += new EventHandler (OnTypingTimeoutExpired);
            typingTimer.Interval = 5000;
        }        

        /// <summary>
        /// Send message to all participant of the current IM session.
        /// </summary>
        /// <param name="message">Message string</param>

        public void SendMessage (string message) {
            
            activity.BeginSend (new ContentType ("text/plain", "utf-8"), message, sendMessageCallback, null);            
        }

        /// <summary>
        /// Invite new participant to the current IM session.
        /// </summary>
        /// <param name="sipAddress">SIP address of the participant to invite</param>

        public void InviteParticipant (string sipAddress) {

            if (session == null || session.LocalParticipant.State == System.Collaboration.ParticipantState.Disconnected) {
                session = realTimeProfile.profile.Signaling.CreateSession ("InstantMessaging",
                                                                           Guid.NewGuid ().ToString (),
                                                                           new InstantMessagingActivityConversationContext ("4"));
                InitializeActivity ();
                typingTimer.Enabled = true;
            }
            
            try {
                activity.BeginInvite (sipAddress, inviteCallback, null);
            }
            catch (Exception ex) {
                ErrorMessage ("Invite failed.\r\n" + ex.ToString () + "\r\n");
                InviteFailed (this, new UnhandledExceptionEventArgs (ex, false));
            }
        }

        /// <summary>
        /// Leave activity.
        /// </summary>

        public void LeaveActivity () {

            if (activity != null) {
                activity.Dispose ();
                activity = null;
            }

            if (session != null) {
                session.Leave ();
                session = null;
            }
        }            

        /// <summary>
        /// Should be called by the component user when local participant starts typing.
        /// Called automatically if TypingControl is initialized.
        /// </summary>

        public void LocalParticipantStartedTyping () {
            
            if (activity != null) {
                activity.TypingState = Microsoft.Collaboration.Activity.TypingState.Typing;
            }
        }

        /// <summary>
        /// Should be called by the component user when local participant stops typing.
        /// Called automatically if TypingControl is initialized.
        /// </summary>

        public void LocalParticipantStoppedTyping () {
            
            if (activity != null) {
                activity.TypingState = Microsoft.Collaboration.Activity.TypingState.Idle;
            }
        }

        /// <summary>
        /// Creates and initializes IM activity for current session.
        /// </summary>

        private void InitializeActivity () {

            activity = new InstantMessagingActivity (session);

            acceptCallback = new AsyncCallback (AcceptCallback);
            sendMessageCallback = new AsyncCallback (SendMessageCallback);
            inviteCallback = new AsyncCallback (InviteCallback);

            activity.MessageReceived += new MessageReceivedEventHandler (OnMessageReceived);
            activity.Participants.ItemAdded += new CollectionEventHandler (OnParticipantAdded);
            activity.Participants.ItemRemoved += new CollectionEventHandler (OnParticipantRemoved);
        }

        /// <summary>
        /// Unregisters message box event handlers.
        /// </summary>

        private void UnregisterMessageBoxEventHandlers () {

            if (messageBox != null) {
                messageBox.TextChanged -= new EventHandler (OnMessageBoxTextChanged);                
            }
        }

        /// <summary>
        /// Registers message box event handlers.
        /// </summary>

        private void RegisterMessageBoxEventHandlers () {

            if (messageBox != null) {
                messageBox.TextChanged += new EventHandler (OnMessageBoxTextChanged);                
            }
        }

        /// <summary>
        /// Unregisters Send button event handlers.
        /// </summary>

        private void UnregisterSendButtonEventHandlers () {            

            if (sendButton != null) {
                sendButton.Click -= new EventHandler (OnSendButtonClick);
            }
        }

        /// <summary>
        /// Registers Send button event handlers.
        /// </summary>

        private void RegisterSendButtonEventHandlers () {

            if (sendButton != null) {
                sendButton.Click += new EventHandler (OnSendButtonClick);
            }
        }

        /// <summary>
        /// Initialize signaling session.
        /// </summary>        

        private void InitializeSession () {

            System.Collaboration.SignalingParticipant inviter = session.Inviter;
            StringBuilder text = new StringBuilder ();            

            text.AppendFormat ("Got an invite from {0}. Accepted.", ParticipantName (inviter));
            InformationalMessage (text.ToString ());

            CancelEventArgs cancelEventArgs = new CancelEventArgs ();
            InviteReceived (session, cancelEventArgs);
            if (cancelEventArgs.Cancel) {
                session.Decline ();                
                session = null;
                return;
            }

            Type[] imActivityType = { typeof (InstantMessagingActivityConversationContext) };
            InstantMessagingActivityConversationContext ctx = session.GetConversationContext (imActivityType) as InstantMessagingActivityConversationContext;

            try {

                InitializeActivity ();                
                typingTimer.Enabled = true;

                foreach (InstantMessagingActivityParticipant p in activity.Participants) {

                    if (p != activity.LocalParticipant) {
                        RegisterParticipantEventHandlers (p);
                    }
                }

                IAsyncResult asyncResult = activity.BeginAccept (acceptCallback, session.Inviter.RealTimeAddress);
            }
            catch (Exception ex) {
                ErrorMessage ("Accept failed.");
                AcceptFailed (this, new UnhandledExceptionEventArgs (ex, false));
            }
        }

        /// <summary>
        /// Called when session received event gets raised.
        /// </summary>

        internal void OnSessionReceived (object sender, IncomingSessionEventArgs e) {

            session = e.Session;
            InitializeSession ();
        }

        /// <summary>
        /// Called when new message has arrived.
        /// </summary>

        private void OnMessageReceived (object sender, MessageReceivedEventArgs e) {
            
            if (e.ContentType.MimeType.StartsWith ("text/")) {
                
                InstantMessagingActivityParticipant p = sender as InstantMessagingActivityParticipant;
                string message = e.StringBody;

                OutputMessage (p, p.LastMessageReceived, message);

                MessageReceived (sender, e);                
            }
        }        

        /// <summary>
        /// Called when the activity completes an Invite operation.
        /// </summary>

        private void InviteCallback (IAsyncResult asyncResult) {

            try {
                activity.EndInvite (asyncResult);
            }
            catch (Exception ex) {
                ErrorMessage ("Invite failed.\r\n" + ex.ToString ());
                InviteFailed (this, new AsyncEventArgs (ex, asyncResult));
            }
        }

        /// <summary>
        /// Called when the provider completes an Accept operation.
        /// </summary>

        private void AcceptCallback (IAsyncResult asyncResult) {

            try {
                activity.EndAccept (asyncResult);
            }
            catch (Exception ex) {
                ErrorMessage ("Accept failed.");
                AcceptFailed (this, new AsyncEventArgs (ex, asyncResult));
            }
        }

        /// <summary>
        /// Called when the activity completes the Send operation.
        /// </summary>

        private void SendMessageCallback (IAsyncResult asyncResult) {

            try {
                
                ICollection c = activity.EndSend (asyncResult);                

                if (c != null && c.Count > 0) {

                    StringBuilder sb = new StringBuilder ();
                    bool anyFailed = false;
                                
                    foreach (SendStatus s in c) {

                        if (s.State == SendState.Failed) {

                            anyFailed = true;

                            if (s.Exception != null) {
                                sb.AppendFormat ("\r\n  {0} ({1}): {2}", 
                                                 s.Participant.DisplayName, 
                                                 s.Participant.RealTimeAddress, 
                                                 s.Exception.Message);
                            }   
                            else {                            
                                sb.AppendFormat ("\r\n  {0} ({1})", 
                                                 s.Participant.DisplayName, 
                                                 s.Participant.RealTimeAddress);
                            }
                        }
                    }
                
                    if (anyFailed) {
                        ErrorMessage ("Send operation failed for the following recipients:\r\n" + sb.ToString ());                  
                    }
                }

                if (SendMessageSucceeded != null) {
                    SendMessageSucceeded (this, new SendMessageSucceededEventArgs (c));
                }
            }
            catch (Exception ex) {
                ErrorMessage ("Send message failed.\r\n" + ex.ToString ());
                SendMessageFailed (this, new AsyncEventArgs (ex, asyncResult));
            }
        }

        /// <summary>
        /// Adds event handlers for specific participant.
        /// </summary>

        private void RegisterParticipantEventHandlers (InstantMessagingActivityParticipant p) {

            p.ConnectionStateChanged += new EventHandler (OnParticipantStateChanged);
            p.DisplayNameChanged += new EventHandler (OnParticipantDisplayNameChanged);
            p.TypingStateChanged += new EventHandler (OnParticipantTypingStateChanged);
        }

        /// <summary>
        /// Removes event handlers for specific participant.
        /// </summary>

        private void UnregisterParticipantEventHandlers (InstantMessagingActivityParticipant p) {

            p.ConnectionStateChanged -= new EventHandler (OnParticipantStateChanged);
            p.DisplayNameChanged -= new EventHandler (OnParticipantDisplayNameChanged);
            p.TypingStateChanged -= new EventHandler (OnParticipantTypingStateChanged);
        }

        /// <summary>
        /// Called when connection state of participant has changed.
        /// </summary>

        private void OnParticipantStateChanged (object sender, EventArgs e) {

            InstantMessagingActivityParticipant p = sender as InstantMessagingActivityParticipant;

            if (p != null) {

                StringBuilder text = new StringBuilder ();            
                
                if (p.ConnectionState == Microsoft.Collaboration.Activity.ConnectionState.Connected) {
                    
                    text.AppendFormat ("{0} has joined.", ParticipantName (p));
                    InformationalMessage (text.ToString ());
                    
                    ParticipantJoined (p, null);
                }
                else if (p.ConnectionState == Microsoft.Collaboration.Activity.ConnectionState.Disconnected) {

                    text.AppendFormat ("{0} has left.", ParticipantName (p));
                    InformationalMessage (text.ToString ());
                    
                    ParticipantLeft (p, null);
                }
            }
        }

        /// <summary>
        /// Called when display name of participant has changed.
        /// </summary>

        private void OnParticipantDisplayNameChanged (object sender, EventArgs e) {

            InstantMessagingActivityParticipant p = sender as InstantMessagingActivityParticipant;

            if (p != null) {
                ParticipantDisplayNameChanged (p, null);
            }
        }

        /// <summary>
        /// Called when typing state of participant has changed.
        /// </summary>

        private void OnParticipantTypingStateChanged (object sender, EventArgs e) {

            InstantMessagingActivityParticipant p = sender as InstantMessagingActivityParticipant;

            if (p != null) {

                StringBuilder text = new StringBuilder ();            
                
                if (p.TypingState == Microsoft.Collaboration.Activity.TypingState.Typing) {

                    text.AppendFormat ("{0} has started typing.", ParticipantName (p));
                    InformationalMessage (text.ToString ());

                    ParticipantStartedTyping (p, null);
                }
                else {

                    text.AppendFormat ("{0} has stopped typing.", ParticipantName (p));
                    InformationalMessage (text.ToString ());

                    ParticipantStoppedTyping (p, null);
                }
            }
        }

        /// <summary>
        /// Called when participant has been added to the collection.
        /// </summary>

        private void OnParticipantAdded (object sender, CollectionEventArgs e) {

            InstantMessagingActivityParticipant p = e.Target as InstantMessagingActivityParticipant;

            if (p != null) {
                RegisterParticipantEventHandlers (p);
            }
        }

        /// <summary>
        /// Called when participant has been removed from the collection.
        /// </summary>

        private void OnParticipantRemoved (object sender, CollectionEventArgs e) {

            InstantMessagingActivityParticipant p = e.Target as InstantMessagingActivityParticipant;

            if (e.Target as InstantMessagingActivityParticipant != null) {
                UnregisterParticipantEventHandlers (p);
            }
        }

        /// <summary>
        /// Called when message box text changed. Automatically switches typing state if necessary.
        /// </summary>

        private void OnMessageBoxTextChanged (object sender, System.EventArgs e) {

            if (messageBox.Text.Length == 0) {
                LocalParticipantStoppedTyping ();
            }
            else {

                if (typingTimer.Enabled) {
                    typingTimer.Stop ();
                }

                typingTimer.Start ();
                LocalParticipantStartedTyping ();
            }
        }

        /// <summary>
        /// Called when user click Send button.
        /// </summary>

        private void OnSendButtonClick (object sender, System.EventArgs e) {

            if (messageBox == null) {
                return;
            }

            else {                
                
                string message = messageBox.Text;

                SendMessage (message);
                OutputMessage (LocalParticipant, DateTime.Now, message);
                messageBox.Clear ();
            }
        }

        /// <summary>
        /// Callback that monitors content of the typing control and automatically
        /// switches typing state if necessary.
        /// </summary>

        private void OnInviteButtonClick (object sender, System.EventArgs e) {

            // TODO
        }

        /// <summary>
        /// Callback that returns typing state back to idle after a few
        /// seconds of inactivity.
        /// </summary>

        private void OnTypingTimeoutExpired (object sender, EventArgs e) {
            
            typingTimer.Stop ();
            LocalParticipantStoppedTyping ();
        }

        /// <summary>
        /// Returns pretty signaling participant name.
        /// </summary>        

        private string ParticipantName (SignalingParticipant p) {
            
            if (p.DisplayName != null && p.DisplayName.Length != 0) {
                return p.DisplayName;
            }
            else {
                return p.RealTimeAddress;
            }
        }

        /// <summary>
        /// Returns pretty activity participant name.
        /// </summary>        

        private string ParticipantName (ActivityParticipant p) {
            
            if (p.DisplayName != null && p.DisplayName.Length != 0) {
                return p.DisplayName;
            }
            else {
                return p.RealTimeAddress;
            }
        }

        /// <summary>
        /// Outputs informational message to message history control.
        /// </summary>
        /// <param name="message">Message to output</param>

        private void InformationalMessage (string message) {                        
            
            if (messageHistoryBox != null) {
            
                RichTextBox rich = messageHistoryBox as RichTextBox;                
                TextBoxBase plain = messageHistoryBox;

                if (rich != null) {
                    rich.ForeColor = Color.Green;                    
                    rich.SelectionFont = new Font (rich.Font, FontStyle.Regular);            
                    rich.SelectedText += message + "\r\n";
                }
                else {
                    plain.Text += message + "\r\n";
                }
            }
        }

        /// <summary>
        /// Outputs error message to message history control.
        /// </summary>
        /// <param name="message">Message to output</param>

        private void ErrorMessage (string message) {            
        
            if (messageHistoryBox != null) {
            
                RichTextBox rich = messageHistoryBox as RichTextBox;                
                TextBoxBase plain = messageHistoryBox;

                if (rich != null) {
                    rich.ForeColor = Color.Red;                    
                    rich.SelectionFont = new Font (rich.Font, FontStyle.Regular);            
                    rich.SelectedText += message + "\r\n";
                }
                else {
                    plain.Text += message + "\r\n";
                }
            }
        }

        /// <summary>
        /// Outputs sent or received message to message history control. 
        /// </summary>
        /// <param name="participant">Participant who send the message</param>
        /// <param name="dateTime">Date and time when message was sent/received</param>
        /// <param name="message">Message text</param>

        private void OutputMessage (ActivityParticipant participant, DateTime dateTime, string message) {
            
            if (messageHistoryBox != null) {

                RichTextBox rich = messageHistoryBox as RichTextBox;                
                TextBoxBase plain = messageHistoryBox;
                StringBuilder text = new StringBuilder ();
                         
                if (!message.EndsWith ("\r\n")) {
                    message += "\r\n";
                }
                                 
                text.AppendFormat ("[{0}] {1} says:\r\n", DateTime.Now, ParticipantName (LocalParticipant));

                if (rich != null) {
                    rich.SelectionColor = Color.Blue;
                    rich.SelectedText += text;
                    rich.SelectionColor = Color.Black;            
                    rich.SelectionIndent = 24;
                    rich.SelectedText += message;
                    rich.SelectionIndent = 0;            
                }
                else {
                    plain.Text += text + message;                        
                }                    
            }
        }

        /// <summary>
        /// Cleans up any resources being used.
        /// </summary>

        protected override void Dispose (bool disposing) {
            
            if (disposing) {
                LeaveActivity ();
                if (components != null) {
                    components.Dispose ();
                }
            }
            
            base.Dispose (disposing);
        }

        //
        // Run-time only properties.
        //

        /// <summary>
        /// Signaling session object from the underlying API. Read-only property.
        /// </summary>

        [Browsable (false)]
        public SignalingSession Session {
            get {
                return session;
            }
            set {
                if (value != null) {
                    if (session != null || value.MediaType != "InstantMessaging") {
                        value.Decline ();                    
                    }                
                    session = value;                
                    InitializeSession ();
                    if (realTimeProfile != null && realTimeProfile.im == this) {
                        realTimeProfile.im = null;
                    }
                }
                else {
                    if (session != null) {
                        LeaveActivity ();
                    }
                    session = value;
                }
            }
        }

        /// <summary>
        /// IM activity object from the underlying API. Read-only property.
        /// </summary>

        [Browsable (false)]
        public InstantMessagingActivity Activity {
            get {
                return activity;
            }
        }

        /// <summary>
        /// Local participant. Read-only property.
        /// </summary>

        [Browsable (false)]
        public InstantMessagingActivityParticipant LocalParticipant {
            get {
                if (activity == null) {
                    return null;
                }
                else {
                    return activity.LocalParticipant as InstantMessagingActivityParticipant;
                }
            }
        }

        //
        // Run-time and design-time properties.
        //

        /// <summary>
        /// Message box control.
        /// </summary>

        [Description ("Message box control")]
        public TextBoxBase MessageBox {
            get {
                return messageBox;
            }
            set {
                UnregisterMessageBoxEventHandlers ();
                messageBox = value;
                RegisterMessageBoxEventHandlers ();
            }
        }

        /// <summary>
        /// Message history box control.
        /// </summary>

        [Description ("Message history box control")]
        public TextBoxBase MessageHistoryBox {
            get {
                return messageHistoryBox;
            }
            set {
                messageHistoryBox = value;
            }
        }

        /// <summary>
        /// Send button.
        /// </summary>

        [Description ("Send button control")]
        public Button SendButton {
            get {
                return sendButton;
            }
            set {
                UnregisterSendButtonEventHandlers ();
                sendButton = value;
                RegisterSendButtonEventHandlers ();
            }
        }        

        /// <summary>
        /// Real-time profile component.
        /// </summary>

        [Description ("Real-time profile component")]
        public RealTimeProfile RealTimeProfile {
            get {
                return realTimeProfile;
            }
            set {
                if (realTimeProfile != null) {
                    realTimeProfile.im = null;
                }
                realTimeProfile = value;
                if (realTimeProfile != null) {
                    realTimeProfile.im = this;
                }
            }
        }

        //
        // Events.
        //

        /// <summary>
        /// Occurs when Invite comes in.
        /// </summary>

        [Category ("Establishing session")]
        [Description ("Occurs when Invite comes in")]
        public event CancelEventHandler InviteReceived;

        /// <summary>
        /// Occurs when Accept fails.
        /// </summary>

        [Category ("Establishing session")]
        [Description ("Occurs when Accept fails")]
        public event UnhandledExceptionEventHandler AcceptFailed;

        /// <summary>
        /// Occurs when Invite fails.
        /// </summary>

        [Category ("Establishing session")]
        [Description ("Occurs when Invite fails")]
        public event UnhandledExceptionEventHandler InviteFailed;

        /// <summary>
        /// Occurs when sending message succeeds.
        /// </summary>

        [Category ("Messaging")]
        [Description ("Occurs when sending message succeeds")]
        public event SendMessageSucceededEventHandler SendMessageSucceeded;

        /// <summary>
        /// Occurs when sending message fails.
        /// </summary>

        [Category ("Messaging")]
        [Description ("Occurs when sending message fails")]
        public event UnhandledExceptionEventHandler SendMessageFailed;

        /// <summary>
        /// Occurs when incoming message is received.
        /// </summary>

        [Category ("Messaging")]
        [Description ("Occurs when incoming message is received")]
        public event MessageReceivedEventHandler MessageReceived;

        /// <summary>
        /// Occurs when participant joins the chat session.
        /// </summary>

        [Category ("Participant status changing")]
        [Description ("Occurs when participant joins the chat session")]
        public event EventHandler ParticipantJoined;

        /// <summary>
        /// Occurs when participant leaves the chat session.
        /// </summary>

        [Category ("Participant status changing")]
        [Description ("Occurs when participant leaves the chat session")]
        public event EventHandler ParticipantLeft;

        /// <summary>
        /// Occurs when participant starts typing.
        /// </summary>

        [Category ("Participant status changing")]
        [Description ("Occurs when participant starts typing")]
        public event EventHandler ParticipantStartedTyping;

        /// <summary>
        /// Occurs when participant stops typing.
        /// </summary>

        [Category ("Participant status changing")]
        [Description ("Occurs when participant stops typing")]
        public event EventHandler ParticipantStoppedTyping;

        /// <summary>
        /// Occurs when participant changes display name.
        /// </summary>

        [Category ("Participant status changing")]
        [Description ("Occurs when participant changes display name")]
        public event EventHandler ParticipantDisplayNameChanged;

        #region Component Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent () {

        }
        #endregion
    }

    /// <summary>
    /// ContactList class supports contact list management.
    /// </summary>

    public class ContactList : Component {

        //
        // Private properties.
        //

        private System.ComponentModel.Container components = null;

        internal RealTimeProfile realTimeProfile;

        /// <summary>
        /// Initializes an instance of the class.
        /// </summary>

        public ContactList () {            
            InitializeComponent ();
        }

        /// <summary>
        /// Cleans up any resources being used.
        /// </summary>

        protected override void Dispose (bool disposing) {
            if (disposing) {
                if (components != null) {
                    components.Dispose ();
                }
            }
            base.Dispose (disposing);
        }

        /// <summary>
        /// Called when presence subscription is added.
        /// </summary>        

        internal void OnSubscriptionAdded (object sender, CollectionEventArgs e) {            
            PresenceSubscription subs = e.Target as PresenceSubscription;
            subs.PresenceChanged += new EventHandler (OnPresenceChanged);
        }

        /// <summary>
        /// Called when presence subscription is removed.
        /// </summary>        

        internal void OnSubscriptionRemoved (object sender, CollectionEventArgs e) {
        }

        /// <summary>
        /// Called when presence of one of the contacts changes.
        /// </summary>        

        internal void OnPresenceChanged (object sender, EventArgs e) {
            PresenceChanged (sender, e);            
        }

        /// <summary>
        /// Called when contact is added.
        /// </summary>        

        internal void OnContactAdded (object sender, CollectionEventArgs e) {
            ContactAdded (sender, e);
        }

        /// <summary>
        /// Called when contact is removed.
        /// </summary>        

        internal void OnContactRemoved (object sender, CollectionEventArgs e) {
            ContactRemoved (sender, e);
        }

        /// <summary>
        /// Called when contact is added to the group.
        /// </summary>        

        internal void OnContactAddedToGroup (object sender, CollectionEventArgs e) {
            ContactAddedToGroup (sender, e);
        }

        /// <summary>
        /// Called when contact is removed from the group.
        /// </summary>        

        internal void OnContactRemovedFromGroup (object sender, CollectionEventArgs e) {
            ContactRemovedFromGroup (sender, e);
        }

        /// <summary>
        /// Called when group is added.
        /// </summary>        

        internal void OnGroupAdded (object sender, CollectionEventArgs e) {

            int i;
        
            ContactGroupCollection groups = (ContactGroupCollection) sender;
            ContactGroup group = e.Target as ContactGroup;            

            group.ItemAdded += new CollectionEventHandler (OnContactAddedToGroup);
            group.ItemRemoved += new CollectionEventHandler (OnContactRemovedFromGroup);

            GroupAdded (sender, e);

            i = 0;
            foreach (Contact c in group) {
                OnContactAddedToGroup (group, new CollectionEventArgs (i++, c));
            }
        }

        /// <summary>
        /// Called when group is removed.
        /// </summary>        

        internal void OnGroupRemoved (object sender, CollectionEventArgs e) {

            ContactGroupCollection groups = (ContactGroupCollection) sender;
            ContactGroup group = e.Target as ContactGroup;

            group.ItemAdded -= new CollectionEventHandler (OnContactAddedToGroup);
            group.ItemRemoved -= new CollectionEventHandler (OnContactRemovedFromGroup);

            GroupRemoved(sender, e);            
        }        

        /// <summary>
        /// Called when presence access rule is added.
        /// </summary>        

        internal void OnRuleAdded (object sender, CollectionEventArgs e) {
        }

        /// <summary>
        /// Called when presence access rule is removed.
        /// </summary>        

        internal void OnRuleRemoved (object sender, CollectionEventArgs e) {
        }

        //
        // Run-time only properties.
        //

        /// <summary>
        /// Collection of contacts.
        /// </summary>

        [Browsable (false)]
        public ContactCollection Contacts {
            get {
                if (realTimeProfile != null &&
                    realTimeProfile.Profile != null &&
                    realTimeProfile.Profile.PersistedData != null &&
                    realTimeProfile.Profile.PersistedData.ContactsSubscription != null) {
                    return realTimeProfile.Profile.PersistedData.ContactsSubscription.Contacts;
                }
                else {
                    return null;
                }
            }
        }

        /// <summary>
        /// Collection of groups.
        /// </summary>

        [Browsable (false)]
        public ContactGroupCollection Groups {
            get {
                if (realTimeProfile != null &&
                    realTimeProfile.Profile != null &&
                    realTimeProfile.Profile.PersistedData != null &&
                    realTimeProfile.Profile.PersistedData.ContactGroupsSubscription != null) {
                    return realTimeProfile.Profile.PersistedData.ContactGroupsSubscription.ContactGroups;
                }
                else {
                    return null;
                }
            }
        }

        //
        // Run-time and design-time properties.
        //

        /// <summary>
        /// Real-time profile component.
        /// </summary>

        [Description ("Real-time profile component")]
        public RealTimeProfile RealTimeProfile {
            get {
                return realTimeProfile;
            }
            set {                
                if (realTimeProfile != null) {
                    realTimeProfile.ContactList = null;
                }
                realTimeProfile = value;
                if (realTimeProfile != null) {
                    realTimeProfile.ContactList = this;                    
                }
            }
        }

        //
        // Events.
        //        

        /// <summary>
        /// Occurs when new contact is added.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when new contact is added")]
        public event CollectionEventHandler ContactAdded;

        /// <summary>
        /// Occurs when contact is removed.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when contact is removed")]
        public event CollectionEventHandler ContactRemoved;        

        /// <summary>
        /// Occurs when new contact is added to a group.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when new contact is added to a group")]
        public event CollectionEventHandler ContactAddedToGroup;

        /// <summary>
        /// Occurs when contact is removed from a group.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when contact is removed from a group")]
        public event CollectionEventHandler ContactRemovedFromGroup;        
        
        /// <summary>
        /// Occurs when group is added.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when group is added")]
        public event CollectionEventHandler GroupAdded;        

        /// <summary>
        /// Occurs when group is removed.
        /// </summary>

        [Category ("Contact list management")]
        [Description ("Occurs when group is removed")]
        public event CollectionEventHandler GroupRemoved;

        /// <summary>
        /// Occurs when presence of one of contacts changes.
        /// </summary>

        [Category ("Presence management")]
        [Description ("Occurs when presence of one of contacts changes")]
        public event EventHandler PresenceChanged;

        #region Component Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent () {

        }
        #endregion
    }
}