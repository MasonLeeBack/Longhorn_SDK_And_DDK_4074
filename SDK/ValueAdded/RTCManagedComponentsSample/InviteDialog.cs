using System;
using System.Collaboration;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

using Microsoft.Collaboration;
using Microsoft.Collaboration.Activity;

namespace SimpleMessenger
{
	/// <summary>
	/// Summary description for InviteForm.
	/// </summary>
	
	public class InviteDialog : System.Windows.Forms.Form {

        private System.Windows.Forms.Button inviteButton;
        private System.Windows.Forms.Button cancelButton;
        internal System.Windows.Forms.ComboBox realTimeAddress;

        internal ChatForm chatForm;
	
		private System.ComponentModel.Container components = null;

		public InviteDialog (ChatForm cf) {		

            InitializeComponent ();
    
	        chatForm = cf;		            

            foreach (TreeNode groupNode in chatForm.contactListForm.contactList.Nodes) {
                foreach (TreeNode contactNode in groupNode.Nodes) {
                    if (contactNode.ForeColor == Color.Green) {                                               
                        Contact contact = contactNode.Tag as Contact;
                        if (realTimeAddress.Items.IndexOf (contact.RealTimeAddress) == -1) {
                            realTimeAddress.Items.Add (contact.RealTimeAddress);
                        }
                    }
                }
            }

            foreach (SignalingParticipant p in chatForm.im.Session.Participants) {
                if (p.State != ParticipantState.Disconnected) {
                    if (realTimeAddress.Items.IndexOf (p.RealTimeAddress) != -1) {
                        realTimeAddress.Items.Remove (p.RealTimeAddress);                    
                    }
                }
            }

            foreach (TreeNode groupNode in chatForm.contactListForm.contactList.Nodes) {
                foreach (TreeNode contactNode in groupNode.Nodes) {
                    if (contactNode.ForeColor == Color.Green) {                                               
                        Contact contact = contactNode.Tag as Contact;
                        int index = realTimeAddress.Items.IndexOf (contact.RealTimeAddress);
                        if (index >= 0) {
                            string id = contact.DisplayName + " (" + contact.RealTimeAddress + ")";
                            realTimeAddress.Items.RemoveAt (index);
                            realTimeAddress.Items.Insert (index, id);
                        }
                    }
                }
            }
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
            this.inviteButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.realTimeAddress = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // inviteButton
            // 
            this.inviteButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.inviteButton.Enabled = false;
            this.inviteButton.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.inviteButton.Location = new System.Drawing.Point(32, 40);
            this.inviteButton.Name = "inviteButton";
            this.inviteButton.TabIndex = 1;
            this.inviteButton.Text = "&Invite";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.cancelButton.Location = new System.Drawing.Point(184, 40);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "&Cancel";
            // 
            // realTimeAddress
            // 
            this.realTimeAddress.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.realTimeAddress.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.realTimeAddress.Location = new System.Drawing.Point(8, 8);
            this.realTimeAddress.Name = "realTimeAddress";
            this.realTimeAddress.Size = new System.Drawing.Size(272, 21);
            this.realTimeAddress.TabIndex = 3;
            this.realTimeAddress.SelectedIndexChanged += new System.EventHandler(this.realTimeAddress_SelectedIndexChanged);
            // 
            // InviteDialog
            // 
            this.AcceptButton = this.inviteButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(289, 72);
            this.ControlBox = false;
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.realTimeAddress,
                                                                          this.inviteButton,
                                                                          this.cancelButton});
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "InviteDialog";
            this.ShowInTaskbar = false;
            this.Text = "Invite";
            this.ResumeLayout(false);

        }
		#endregion

        private void realTimeAddress_SelectedIndexChanged(object sender, System.EventArgs e) {
            inviteButton.Enabled = realTimeAddress.Text != "";
        }
	}
}
