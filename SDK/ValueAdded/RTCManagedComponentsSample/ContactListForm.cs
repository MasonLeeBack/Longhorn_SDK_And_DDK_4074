using System;
using System.Diagnostics;
using System.Drawing;
using System.Collaboration;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

using Microsoft.Collaboration;
using Microsoft.Collaboration.Activity;

namespace SimpleMessenger {	    
	
	public class ContactListForm : System.Windows.Forms.Form {

        private System.ComponentModel.Container components = null;

        private RtcClient.RealTimeProfile rtp;
        private System.Windows.Forms.StatusBar statusBar;
        internal System.Windows.Forms.TreeView contactList;
        private System.Windows.Forms.StatusBarPanel statusBarPanel;
        private RtcClient.ContactList cl;		
        private TreeNode allContactsNode;
        private TreeNode addGroupNode;
        private ContactGroup draggingFromGroup;
        private Contact draggingContact;
        private bool firstActivation = true;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        
        [STAThread]
        static void Main () {
            Application.Run (new ContactListForm ());
        }

        public ContactListForm () {                        
            InitializeComponent ();                        
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		
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
            System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(ContactListForm));
            this.rtp = new RtcClient.RealTimeProfile();
            this.statusBar = new System.Windows.Forms.StatusBar();
            this.statusBarPanel = new System.Windows.Forms.StatusBarPanel();
            this.contactList = new System.Windows.Forms.TreeView();
            this.cl = new RtcClient.ContactList();
            ((System.ComponentModel.ISupportInitialize)(this.statusBarPanel)).BeginInit();
            this.SuspendLayout();
            // 
            // rtp
            // 
            this.rtp.Domain = "";
            this.rtp.Password = "";
            this.rtp.RealTimeAddress = "";
            this.rtp.UserName = "";
            this.rtp.LogOffSucceeded += new System.EventHandler(this.rtp_LogOffSucceeded);
            this.rtp.LogOnFailed += new System.UnhandledExceptionEventHandler(this.rtp_LogOnFailed);
            this.rtp.LogOnSucceeded += new System.EventHandler(this.rtp_LogOnSucceeded);
            this.rtp.SessionReceived += new System.Collaboration.IncomingSessionEventHandler(this.rtp_SessionReceived);
            // 
            // statusBar
            // 
            this.statusBar.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.statusBar.Location = new System.Drawing.Point(0, 632);
            this.statusBar.Name = "statusBar";
            this.statusBar.Panels.AddRange(new System.Windows.Forms.StatusBarPanel[] {
                                                                                         this.statusBarPanel});
            this.statusBar.ShowPanels = true;
            this.statusBar.Size = new System.Drawing.Size(240, 22);
            this.statusBar.TabIndex = 0;
            // 
            // statusBarPanel
            // 
            this.statusBarPanel.AutoSize = System.Windows.Forms.StatusBarPanelAutoSize.Spring;
            this.statusBarPanel.Text = "Logged off";
            this.statusBarPanel.Width = 224;
            // 
            // contactList
            // 
            this.contactList.AllowDrop = true;
            this.contactList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.contactList.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(204)));
            this.contactList.HotTracking = true;
            this.contactList.ImageIndex = -1;
            this.contactList.Name = "contactList";
            this.contactList.SelectedImageIndex = -1;
            this.contactList.Size = new System.Drawing.Size(240, 632);
            this.contactList.TabIndex = 1;
            this.contactList.KeyDown += new System.Windows.Forms.KeyEventHandler(this.contactList_KeyDown);
            this.contactList.DragOver += new System.Windows.Forms.DragEventHandler(this.contactList_DragOver);
            this.contactList.DoubleClick += new System.EventHandler(this.contactList_DoubleClick);
            this.contactList.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.contactList_ItemDrag);
            this.contactList.DragDrop += new System.Windows.Forms.DragEventHandler(this.contactList_DragDrop);
            // 
            // cl
            // 
            this.cl.RealTimeProfile = this.rtp;
            this.cl.GroupAdded += new System.Collaboration.CollectionEventHandler(this.cl_GroupAdded);
            this.cl.GroupRemoved += new System.Collaboration.CollectionEventHandler(this.cl_GroupRemoved);
            this.cl.ContactRemovedFromGroup += new System.Collaboration.CollectionEventHandler(this.cl_ContactRemovedFromGroup);
            this.cl.ContactRemoved += new System.Collaboration.CollectionEventHandler(this.cl_ContactRemoved);
            this.cl.ContactAddedToGroup += new System.Collaboration.CollectionEventHandler(this.cl_ContactAddedToGroup);
            this.cl.ContactAdded += new System.Collaboration.CollectionEventHandler(this.cl_ContactAdded);
            this.cl.PresenceChanged += new System.EventHandler(this.cl_PresenceChanged);
            // 
            // ContactListForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(240, 654);
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.contactList,
                                                                          this.statusBar});
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ContactListForm";
            this.Text = "Simple Messenger";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.ContactListForm_Closing);
            this.Activated += new System.EventHandler(this.ContactListForm_Activated);
            ((System.ComponentModel.ISupportInitialize)(this.statusBarPanel)).EndInit();
            this.ResumeLayout(false);

        }
		#endregion

        private void UpdateGroup (TreeNode groupNode) {
            int numOnline = 0;
            foreach (TreeNode contactNode in groupNode.Nodes) {
                Contact contact = contactNode.Tag as Contact;                        
                numOnline += contactNode.ForeColor == Color.Green ? 1 : 0;
            }
            groupNode.Text = groupNode.Text.Substring (0, groupNode.Text.LastIndexOf (" (")) + " (" + numOnline + "/" + (groupNode.Nodes.Count - 1) + ")";
        }        

        private void ContactListForm_Activated (object sender, System.EventArgs e) {

            if (firstActivation) {

                firstActivation = false;
        
                LogonDialog logonDialog = new LogonDialog ();
                
                if (logonDialog.ShowDialog () == DialogResult.OK) {

                    rtp.RealTimeAddress = logonDialog.realTimeAddress.Text;
                    rtp.Domain = logonDialog.domain.Text;
                    rtp.UserName = logonDialog.userName.Text;
                    rtp.Password = logonDialog.password.Text;

                    Cursor = Cursors.WaitCursor;
                    rtp.LogOn ();
                    Cursor = Cursors.Default;
                
                    allContactsNode = contactList.Nodes.Add ("All contacts (0/0)");
                    TreeNode addContactNode = allContactsNode.Nodes.Add ("Add contact");
                    addContactNode.ForeColor = Color.Gray;

                    addGroupNode = contactList.Nodes.Add ("Add group");
                    addGroupNode.ForeColor = Color.Gray;
                }
                
                else {
                    Close ();
                }                       
            }
        }        

        private void ContactListForm_Closing (object sender, CancelEventArgs e) {
            Cursor = Cursors.WaitCursor;
            rtp.LogOff ();
            Cursor = Cursors.Default;       
        }

        private void rtp_LogOffSucceeded (object sender, System.EventArgs e) {
            statusBarPanel.Text = "Logged off";            
            contactList.Nodes.Clear ();
        }

        private void rtp_LogOnFailed (object sender, System.UnhandledExceptionEventArgs e) {
            MessageBox.Show ("Log on failed.\n" + e.ExceptionObject.ToString (), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            contactList.Nodes.Clear ();
            firstActivation = true;
            ContactListForm_Activated (null, null);
        }

        private void rtp_LogOnSucceeded (object sender, System.EventArgs e) {
            statusBarPanel.Text = "Logged on";            
            foreach (TreeNode groupNode in contactList.Nodes) {
                groupNode.Expand ();
            }
        }

        private void cl_ContactAdded (object sender, System.Collaboration.CollectionEventArgs e) {
        
            Contact contact = e.Target as Contact;            
                        
            TreeNode newContactNode = new TreeNode (contact.DisplayName);
            allContactsNode.Nodes.Insert (allContactsNode.Nodes.Count - 1, newContactNode);
            newContactNode.Tag = contact;

            int numOnline = 0;
            foreach (TreeNode contactNode in allContactsNode.Nodes) {
                contact = contactNode.Tag as Contact;                        
                numOnline += contactNode.ForeColor == Color.Green ? 1 : 0;
            }
            allContactsNode.Text = allContactsNode.Text.Substring (0, allContactsNode.Text.LastIndexOf (" (")) + " (" + numOnline + "/" + (allContactsNode.Nodes.Count - 1) + ")";
        }

        private void cl_ContactRemoved (object sender, System.Collaboration.CollectionEventArgs e) {                        

            Contact contact = e.Target as Contact;            

            foreach (TreeNode groupNode in contactList.Nodes) {
                foreach (TreeNode contactNode in groupNode.Nodes) {
                    if (contactNode.Tag == contact) {
                        contactNode.Remove ();
                        UpdateGroup (allContactsNode);                    
                    }
                }                                                
            }
        }

        private void cl_ContactAddedToGroup (object sender, System.Collaboration.CollectionEventArgs e) {
            
            Contact contact = e.Target as Contact;
            ContactGroup group = sender as ContactGroup;                        

            foreach (TreeNode groupNode in contactList.Nodes) {
                
                if (groupNode.Tag == group) {
                    
                    TreeNode newContactNode = new TreeNode (contact.DisplayName);
                    groupNode.Nodes.Insert (groupNode.Nodes.Count - 1, newContactNode);
                    newContactNode.Tag = contact;                                        

                    UpdateGroup (groupNode);

                    break;
                }
            }            
        }                

        private void cl_ContactRemovedFromGroup (object sender, System.Collaboration.CollectionEventArgs e) {
        
            Contact contact = e.Target as Contact;
            ContactGroup group = sender as ContactGroup;                        
        
            foreach (TreeNode groupNode in contactList.Nodes) {                                                
                if (groupNode.Tag == group) {
                    foreach (TreeNode contactNode in groupNode.Nodes) {
                        if (contactNode.Tag == contact) {
                            contactNode.Remove ();
                            UpdateGroup (groupNode);
                            return;
                        }
                    }                                    
                }
            }
        }        

        private void cl_GroupAdded (object sender, System.Collaboration.CollectionEventArgs e) {

            TreeNode groupNode;
            TreeNode addContactNode;
            ContactGroup group = e.Target as ContactGroup;

            groupNode = new TreeNode (group.DisplayName + " (0/0)");
            contactList.Nodes.Insert (contactList.Nodes.Count - 1, groupNode);                        
            groupNode.Tag = group;

            addContactNode = groupNode.Nodes.Add ("Add contact");
            addContactNode.ForeColor = Color.Gray;
        }

        private void cl_GroupRemoved (object sender, System.Collaboration.CollectionEventArgs e) {
            
            ContactGroup group = e.Target as ContactGroup;            
            
            foreach (TreeNode node in contactList.Nodes) {
                if (node.Tag == group) {
                    node.Remove ();
                    break;
                }
            }            
        }

        private void contactList_DoubleClick (object sender, System.EventArgs e) {

            TreeNode selectedNode = contactList.SelectedNode;
                        
            if (selectedNode != null) {

                if (selectedNode.ForeColor == Color.Green) {
                    Contact contact = selectedNode.Tag as Contact;
                    if (contact != null) {
                        ChatForm chatForm = new ChatForm (this, rtp, contact.RealTimeAddress);
                        chatForm.Show ();
                    }
                }
                
                else if (selectedNode.ForeColor == Color.Gray) {
                    if (selectedNode.Parent == null) {
                        AddGroupDialog addGroupDialog = new AddGroupDialog ();
                        if (addGroupDialog.ShowDialog () == DialogResult.OK) {
                            ContactGroup newGroup = cl.Groups.CreateContactGroup (addGroupDialog.groupName.Text);
                            try {
                                cl.Groups.Add (newGroup);
                            }
                            catch (Exception) {
                            }
                        }
                    }
                    else {
                        ContactGroup group = selectedNode.Parent.Tag as ContactGroup;
                        AddContactDialog addContactDialog = new AddContactDialog ();                        
                        if (addContactDialog.ShowDialog () == DialogResult.OK) {
                            Contact newContact = cl.Contacts.CreateContact (addContactDialog.realTimeAddress.Text,
                                                                            addContactDialog.displayName.Text,                            
                                                                            true);
                            try {
                                cl.Contacts.Add (newContact);
                                if (group != null) {
                                    group.Add (newContact);
                                }
                            }
                            catch (Exception) {
                            }
                        }
                    }
                }
            }
        }

        private void cl_PresenceChanged (object sender, System.EventArgs e) {

            PresenceSubscription subs = sender as PresenceSubscription;
            
            foreach (TreeNode groupNode in contactList.Nodes) {

                foreach (TreeNode contactNode in groupNode.Nodes) {
                    Contact contact = contactNode.Tag as Contact;
                    if (contact != null && contact.RealTimeAddress == subs.RealTimeAddress) {
                        contactNode.ForeColor = Color.Black;                        
                        foreach (EndpointPresence p in subs.Presence.EndpointPresenceList) {
                            if (p.PresenceState != PresenceState.Offline) {
                                contactNode.ForeColor = Color.Green;
                                break;
                            }
                        }                        
                    }                    
                }

                UpdateGroup (groupNode);
            }
        }

        private void rtp_SessionReceived (object sender, System.Collaboration.IncomingSessionEventArgs e) {
            ChatForm chatForm = new ChatForm (this, rtp, e.Session);
            chatForm.Show ();       
        }

        private void contactList_DragDrop (object sender, System.Windows.Forms.DragEventArgs e) {

            if (draggingContact != null) {

                Point p = new Point (e.X, e.Y);
                p = contactList.PointToClient (p);

                TreeNode node = contactList.GetNodeAt (p.X, p.Y);                

                if (node != null && node.Parent == null) {

                    ContactGroup group = node.Tag as ContactGroup;

                    if (draggingFromGroup != group) {
                        if (draggingFromGroup != null) {
                            draggingFromGroup.Remove (draggingContact);                            
                        }
                        if (group != null) {
                            group.Add (draggingContact);
                        }
                    }

                    //node.Expand ();
                }
            }            
        }                

        private void contactList_ItemDrag (object sender, System.Windows.Forms.ItemDragEventArgs e) {
            TreeNode node = e.Item as TreeNode;
            if (node != null) {
                Contact contact = node.Tag as Contact;
                if (contact != null) {
                    draggingContact = contact;
                    draggingFromGroup = node.Parent.Tag as ContactGroup;
                    contactList.DoDragDrop ("", DragDropEffects.Copy | DragDropEffects.Move);                    
                }
            }            
        }

        private void contactList_DragOver (object sender, System.Windows.Forms.DragEventArgs e) {           
            
            if (draggingContact != null) {

                Point p = new Point (e.X, e.Y);
                p = contactList.PointToClient (p);

                TreeNode node = contactList.GetNodeAt (p.X, p.Y);                
            
                if (node != null && node.Parent == null) {

                    ContactGroup group = node.Tag as ContactGroup;

                    if (draggingFromGroup == group) {
                        e.Effect = DragDropEffects.None;
                    }
                    else if (draggingFromGroup == null) {
                        e.Effect = DragDropEffects.Copy;
                    }
                    else {
                        e.Effect = DragDropEffects.Move;
                    }
                }
                else {
                    e.Effect = DragDropEffects.None;                    
                }
            }
        }

        private void contactList_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e) {
            
            if (e.KeyCode == Keys.Delete) {
                if (contactList.SelectedNode != null) {                                        
                    ContactGroup group = contactList.SelectedNode.Tag as ContactGroup;
                    if (group != null) {
                        cl.Groups.Remove (group);
                    }
                    else {
                        Contact contact = contactList.SelectedNode.Tag as Contact;
                        if (contact != null) {
                            group = contactList.SelectedNode.Parent.Tag as ContactGroup;    
                            if (group == null) {
                                cl.Contacts.Remove (contact);
                            }
                            else {
                                group.Remove (contact);
                            }
                        }
                    }
                }
            }
        }
    }
}
