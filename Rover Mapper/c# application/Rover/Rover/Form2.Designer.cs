﻿namespace Rover
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.ports = new System.Windows.Forms.ComboBox();
            this.detach = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(166, 91);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Save";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM port:";
            // 
            // ports
            // 
            this.ports.FormattingEnabled = true;
            this.ports.Location = new System.Drawing.Point(166, 33);
            this.ports.Name = "ports";
            this.ports.Size = new System.Drawing.Size(75, 21);
            this.ports.TabIndex = 2;
            this.ports.SelectedIndexChanged += new System.EventHandler(this.ports_SelectedIndexChanged);
            // 
            // detach
            // 
            this.detach.Location = new System.Drawing.Point(26, 91);
            this.detach.Name = "detach";
            this.detach.Size = new System.Drawing.Size(75, 23);
            this.detach.TabIndex = 3;
            this.detach.Text = "Detach ";
            this.detach.UseVisualStyleBackColor = true;
            this.detach.Click += new System.EventHandler(this.detach_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(259, 132);
            this.Controls.Add(this.detach);
            this.Controls.Add(this.ports);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Name = "Form2";
            this.Text = "Settings";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox ports;
        private System.Windows.Forms.Button detach;
    }
}