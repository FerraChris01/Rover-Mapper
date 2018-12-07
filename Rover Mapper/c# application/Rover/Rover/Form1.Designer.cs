namespace Rover
{
    partial class Form1
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Pulire le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.bStart = new System.Windows.Forms.Button();
            this.pDraw = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.opzioniToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.esportaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DEMO = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.lOrientamento = new System.Windows.Forms.Label();
            this.lDebug = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // bStart
            // 
            this.bStart.Location = new System.Drawing.Point(28, 37);
            this.bStart.Name = "bStart";
            this.bStart.Size = new System.Drawing.Size(75, 23);
            this.bStart.TabIndex = 0;
            this.bStart.Text = "Start";
            this.bStart.UseVisualStyleBackColor = true;
            this.bStart.Click += new System.EventHandler(this.bStart_Click);
            // 
            // pDraw
            // 
            this.pDraw.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pDraw.Location = new System.Drawing.Point(214, 12);
            this.pDraw.Name = "pDraw";
            this.pDraw.Size = new System.Drawing.Size(801, 645);
            this.pDraw.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(28, 81);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Stop";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(28, 418);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 161);
            this.textBox1.TabIndex = 3;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1027, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.opzioniToolStripMenuItem,
            this.esportaToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // opzioniToolStripMenuItem
            // 
            this.opzioniToolStripMenuItem.Name = "opzioniToolStripMenuItem";
            this.opzioniToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.opzioniToolStripMenuItem.Text = "Settings";
            this.opzioniToolStripMenuItem.Click += new System.EventHandler(this.opzioniToolStripMenuItem_Click);
            // 
            // esportaToolStripMenuItem
            // 
            this.esportaToolStripMenuItem.Name = "esportaToolStripMenuItem";
            this.esportaToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.esportaToolStripMenuItem.Text = "Export";
            // 
            // DEMO
            // 
            this.DEMO.Location = new System.Drawing.Point(28, 602);
            this.DEMO.Name = "DEMO";
            this.DEMO.Size = new System.Drawing.Size(100, 26);
            this.DEMO.TabIndex = 5;
            this.DEMO.Text = "Demo";
            this.DEMO.UseVisualStyleBackColor = true;
            this.DEMO.Click += new System.EventHandler(this.DEMO_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 123);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Compass";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // lOrientamento
            // 
            this.lOrientamento.AutoSize = true;
            this.lOrientamento.Location = new System.Drawing.Point(25, 340);
            this.lOrientamento.Name = "lOrientamento";
            this.lOrientamento.Size = new System.Drawing.Size(0, 13);
            this.lOrientamento.TabIndex = 7;
            this.lOrientamento.Click += new System.EventHandler(this.label2_Click);
            // 
            // lDebug
            // 
            this.lDebug.AutoSize = true;
            this.lDebug.Location = new System.Drawing.Point(25, 384);
            this.lDebug.Name = "lDebug";
            this.lDebug.Size = new System.Drawing.Size(39, 13);
            this.lDebug.TabIndex = 8;
            this.lDebug.Text = "Debug";
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(28, 166);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(170, 170);
            this.panel1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1027, 669);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.lOrientamento);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lDebug);
            this.Controls.Add(this.DEMO);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pDraw);
            this.Controls.Add(this.bStart);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Mapper";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bStart;
        private System.Windows.Forms.Panel pDraw;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem opzioniToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem esportaToolStripMenuItem;
        private System.Windows.Forms.Button DEMO;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lOrientamento;
        private System.Windows.Forms.Label lDebug;
        private System.Windows.Forms.Panel panel1;
    }
}

