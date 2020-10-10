using System;
using System.Collaboration;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using Microsoft.Collaboration;
using Microsoft.Collaboration.Activity;

using RtcClient;

namespace SimpleMessenger {
    
    public class ChatForm : System.Windows.Forms.Form {        
        
        private System.Windows.Forms.RichTextBox messageHistory;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.TextBox message;
        internal RtcClient.InstantMessaging im;
        internal ContactListForm contactListForm;
        private System.Windows.Forms.MainMenu chatFormMenu;
        private System.Windows.Forms.MenuItem inviteMenuItem;
        
        private System.ComponentModel.Container components = null;

        public ChatForm (ContactListForm clf)  {

            //
            // Required for Windows Form Designer support
            //

            InitializeComponent ();

            contactListForm = clf;
        }

        public ChatForm (ContactListForm clf, RtcClient.RealTimeProfile rtp, string realTimeAddress)  {

            //
            // Required for Windows Form Designer support
            //            

            InitializeComponent ();

            contactListForm = clf;

            im.RealTimeProfile = rtp;            
            im.InviteParticipant (realTimeAddress);
        }

        public ChatForm (ContactListForm clf, RtcClient.RealTimeProfile rtp, SignalingSession session)  {

            //
            // Required for Windows Form Designer support
            //            

            InitializeComponent ();            

            contactListForm = clf;

            im.RealTimeProfile = rtp;
            im.Session = session;            
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// 
        protected override void Dispose (bool disposing) {
            if (disposing) {                
                if (components != null) {
                    components.Dispose ();
                }
            }
            base.Dispose (disposing);
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(ChatForm));
            this.messageHistory = new System.Windows.Forms.RichTextBox();
            this.sendButton = new System.Windows.Forms.Button();
            this.message = new System.Windows.Forms.TextBox();
            this.im = new RtcClient.InstantMessaging();
            this.chatFormMenu = new System.Windows.Forms.MainMenu();
            this.inviteMenuItem = new System.Windows.Forms.MenuItem();
            this.SuspendLayout();
            // 
            // messageHistory
            // 
            this.messageHistory.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.messageHistory.Location = new System.Drawing.Point(8, 8);
            this.messageHistory.Name = "messageHistory";
            this.messageHistory.ReadOnly = true;
            this.messageHistory.Size = new System.Drawing.Size(256, 560);
            this.messageHistory.TabIndex = 3;
            this.messageHistory.Text = "";
            // 
            // sendButton
            // 
            this.sendButton.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.sendButton.Location = new System.Drawing.Point(200, 576);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(64, 64);
            this.sendButton.TabIndex = 2;
            this.sendButton.Text = "Send";
            // 
            // message
            // 
            this.message.AcceptsReturn = true;
            this.message.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.message.Location = new System.Drawing.Point(8, 576);
            this.message.Multiline = true;
            this.message.Name = "message";
            this.message.Size = new System.Drawing.Size(184, 64);
            this.message.TabIndex = 1;
            this.message.Text = "";
            // 
            // im
            // 
            this.im.MessageBox = this.message;
            this.im.MessageHistoryBox = this.messageHistory;
            this.im.RealTimeProfile = null;
            this.im.SendButton = this.sendButton;
            this.im.Session = null;
            this.im.ParticipantJoined += new System.EventHandler(this.im_ParticipantJoined);
            this.im.ParticipantLeft += new System.EventHandler(this.im_ParticipantLeft);
            // 
            // chatFormMenu
            // 
            this.chatFormMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                         this.inviteMenuItem});
            // 
            // inviteMenuItem
            // 
            this.inviteMenuItem.Index = 0;
            this.inviteMenuItem.Text = "&Invite";
            this.inviteMenuItem.Click += new System.EventHandler(this.inviteMenuItem_Click);
            // 
            // ChatForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(272, 650);
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.message,
                                                                          this.sendButton,
                                                                          this.messageHistory});
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.chatFormMenu;
            this.Name = "ChatForm";
            this.Resize += new System.EventHandler(this.ChatForm_Resize);
            this.Closing += new System.ComponentModel.CancelEventHandler(this.ChatForm_Closing);
            this.Load += new System.EventHandler(this.ChatForm_Resize);
            this.ResumeLayout(false);

        }
        #endregion

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

        private void UpdateTitle (ActivityParticipant excluded) {

            string title;

            if (im.Session != null) {
                
                title = "";
                
                foreach (ActivityParticipant p in im.Activity.Participants) {
                    if (p != im.LocalParticipant && p != excluded) {
                        if (title != "") {
                            title += ", ";
                        }
                        title += ParticipantName (p);
                    }
                }

                Text = title;
            }
        }                        

        private void ChatForm_Resize (object sender, System.EventArgs e) {

            messageHistory.Size = Size + new Size (-25, -145);

            message.Location = new Point (8, Size.Height - 129);
            message.Size = new Size (Size.Width - 97, 64);

            sendButton.Location = new Point (Size.Width - 81, Size.Height - 129);
        }

        private void inviteMenuItem_Click (object sender, System.EventArgs e) {
            
            InviteDialog inviteDialog = new InviteDialog (this);
            
            if (inviteDialog.ShowDialog (this) == DialogResult.OK) {
                string s = inviteDialog.realTimeAddress.Text;
                s = s.Substring (s.LastIndexOf ("(") + 1);
                s = s.Substring (0, s.Length - 1);
                im.InviteParticipant (s);
            }
        }        

        private void ChatForm_Closing (object sender, System.ComponentModel.CancelEventArgs e) {
            im.LeaveActivity ();
        }

        private void im_ParticipantJoined (object sender, System.EventArgs e) {
            UpdateTitle (null);        
        }

        private void im_ParticipantLeft (object sender, System.EventArgs e) {
            UpdateTitle (sender as ActivityParticipant);        
        }
    }
}