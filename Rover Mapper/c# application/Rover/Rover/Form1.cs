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


    //@author Peduzzi

    public partial class Form1 : Form
    {
        //Attributi 

        //Porta seriale al solo scopo di test (Broch la sostituirà con la lettura via bluetooth)
        //private SerialPort bt;
        private CStringDecoder sD = null;

        private String comPort = null;

        //Classe per la gestionde della mappa
        CMappa map;

        //Valore di scala per la rappresentazione dei punti
        int scala;


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

            sD = new CStringDecoder("COM5", 9600); 

            map = new CMappa();
            scala = 10;

            g = pDraw.CreateGraphics();
            pen = new Pen(Color.Red);

        }


        //Ogni volta che si ricevono dati da arduino
        private void bt_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            sD.leggiRiga();

            this.BeginInvoke((MethodInvoker)delegate ()
            {
                textBox1.Text = sD.ReadLine();
                disegna(sD.getDistDx(), sD.getDistSx(), sD.getOrientamento());


            });
            //StreamWriter log = new StreamWriter("log.txt", true);

            //log.WriteLine("riga"+sD.riga);
            //log.Close();
            //this.BeginInvoke((MethodInvoker)delegate ()
            //{

            //   
            //});
            //this.BeginInvoke((MethodInvoker)delegate ()
            //{
            //    textBox1.Text += "ciao";
            //});


        }

        //Scala e disegna nel piano con asse y ribaltato
        private void disegnaPunto(Point p)
        {


            Point ptW = new Point();
            ptW.X = p.X * scala + pDraw.Width / 2;
            ptW.Y = pDraw.Height / 2 - p.Y /* * scala*/;

            drawPixel(ptW);
        }


        private void disegna(int distDx, int distSx, int orientamento)
        {

            map.add(distDx, distSx, orientamento); //Carattere 1 = dist da Dx - carattere 2 = dist da Sx - carattere 3 = angolo orienamento
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
            //bt.inviaSeriale("ciao");
            /*bt.WriteLine("ciao"); */          //prova
                                                //if (bt.getTesto() != "")
                                                //textBox1.Text = bt.getTesto();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //invio W quando viene premuto il tasto, TODO l'arudino capisce e si ferma
            //bt.Write("W");
        }

        private void opzioniToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 frm = new Form2(comPort);
            frm.StartPosition = FormStartPosition.CenterScreen;
            DialogResult res = frm.ShowDialog();

            if (res == DialogResult.OK)
            {
                comPort = frm.getPort();
                openPort();
            }
        }
        private void openPort()
        {
            try
            {
                if (sD != null && sD.IsOpen) sD.Close();
                {
                    sD = new CStringDecoder(comPort, 9600);
                    sD.DtrEnable = true;
                    sD.Open();
                    sD.DataReceived += bt_DataReceived;
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show("Error IO: " + ex.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error COM: " + ex.Message);
            }
        }

        private void DEMO_Click(object sender, EventArgs e)
        {
            StreamReader f = new StreamReader("input.csv");
            String riga = "";
            while (!f.EndOfStream)
            {
                riga = f.ReadLine();
                disegna(sD.getDistDx(riga), sD.getDistSx(riga), sD.getOrientamento(riga));
            }
            f.Close();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
    }
}
