using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rover
{


    //@author Peduzzi Samuele 

    public partial class Form1 : Form
    {
        //Attributi 

        //Porta seriale al solo scopo di test (Broch la sostituirà con la lettura via bluetooth)
        private SerialPort bt;

        //Classe per la gestionde della mappa
        CMappa map;
        //Valore di scala per la rappresentazione dei punti
        int scala; 
        int val0;
        int val1;
        int val2;
        String[] campi;


        //Drawing class
        Graphics g;
        Pen pen;
        Brush b = (Brush)Brushes.Black;

        //Metodi
        //Utilizzare questo metodo per disegnare un punto
        private void drawPixel(Point p)
        {
            g.FillRectangle(b, p.X, p.Y, 2, 2);
        }

        //Costruttore
        public Form1()
        {
            //Inizializzazione componenti grafiche 
            InitializeComponent();

            this.StartPosition = FormStartPosition.CenterScreen;

            map = new CMappa();

            scala = 10;

            val0 = 0;
            val1 = 0;
            val2 = 0;


            g = pDraw.CreateGraphics();
            pen = new Pen(Color.Red);

            //Porta seriale da sostituire con comunicazione bluetooth !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //https://social.msdn.microsoft.com/Forums/vstudio/en-US/92888551-10c7-4bde-86f3-3445d9293ada/bluetooth-communication-using-serial-ports?forum=csharpgeneral
            //Creazione porta seriale per bluetooth 
            bt = new SerialPort("COM7", 9600);  //quella in uscita

            bt.DtrEnable = true;
            //bt.Open();
            bt.DataReceived += bt_DataReceived;

        }
        //Ogni volta che si ricevono dati da arduino
        private void bt_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String s = bt.ReadLine();

            disegna(s);
        }

        private void disegnaPunto(Point p)
        {

            Point ptW  = new Point();
            ptW.X = p.X * scala + pDraw.Width / 2;
            ptW.Y = pDraw.Height - p.Y * scala;

            drawPixel(ptW);
        }


        private void disegna(string riga)
        {
            campi = riga.Split(';');

            int.TryParse(campi[0], out val0);
            int.TryParse(campi[1], out val1);
            int.TryParse(campi[2], out val2);

            map.add(val0, val1, val2); //Carattere 1 = dist da Dx - carattere 2 = dist da Sx - carattere 3 = angolo orienamento
            disegnaPunto(map.pDx.Last<Point>());
            disegnaPunto(map.pSx.Last<Point>());

            //ROBA PER TESTARE IL BLUETOOTH....
            //this.BeginInvoke((MethodInvoker)delegate ()
            //{
            //    textBox1.Text += line;
            //});
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void bStart_Click(object sender, EventArgs e)
        {
            //invio S quando viene premuto il tasto, TODO l'arudino capisce e starta
            //bt.Write("S");
            /*bt.WriteLine("ciao"); */          //prova

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //invio W quando viene premuto il tasto, TODO l'arudino capisce e si ferma
            //bt.Write("W");
        }

        private void opzioniToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form settingsForm = new Form();
            settingsForm.Show();
        }



        private void Form2_Load(object sender, EventArgs e)
        {
            Form2 newForm = new Form2();
            newForm.StartPosition = FormStartPosition.CenterScreen;
            newForm.Show();
        }

        private void DEMO_Click(object sender, EventArgs e)
        {
            StreamReader f = new StreamReader("input.csv");
            String riga = "";
            while (!f.EndOfStream)
            {
                riga = f.ReadLine();
                disegna(riga);
            }
            f.Close();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
    }
}
