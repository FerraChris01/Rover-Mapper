using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rover
{
    public partial class Form2 : Form
    {
        public string ReturnText { get; set; }
        public Form2(String porta)
        {
            InitializeComponent();
            foreach (string s in System.IO.Ports.SerialPort.GetPortNames())
            {
                ports.Items.Add(s);
                ports.SelectedItem = porta;
            }
        }
        public String getPort()
        {
            return ReturnText;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                ReturnText = this.ports.SelectedItem.ToString();
                //this.Visible = false;
                this.DialogResult = DialogResult.OK;
                this.Close();

            }
            catch (System.NullReferenceException ex)
            {
                MessageBox.Show("You must select a COM port");
            }
            catch (Exception ex)
            {
                MessageBox.Show("You must select a COM port: " + ex.Message);
            }
        }

        private void Form2_Load(object sender, EventArgs e)
        {
        }

        private void ports_SelectedIndexChanged(object sender, EventArgs e)
        {
            ReturnText = this.ports.SelectedItem.ToString();
        }
    }
}
