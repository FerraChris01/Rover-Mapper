using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
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

        private bool status = false;

        //Classe per la gestionde della mappa
        CMappa map;

        

        //Valore di scala per la rappresentazione dei punti
        int scala;
        //Creazione Bussola
        Compass bussola;

        //Drawing class
        Graphics gMap;
        Graphics gComp;
        Pen pen;
        Brush b = (Brush)Brushes.Black;

        //Metodi
        //Utilizzare questo metodo per disegnare un punto
        private void drawPixel(Graphics g, Point p)
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
            

            gMap = pDraw.CreateGraphics();
            gComp = pCompass.CreateGraphics();
            pen = new Pen(Color.Red);

            bussola = new Compass();

        }


        //Ogni volta che si ricevono dati da arduino
        private void bt_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            sD.leggiRiga();


            this.BeginInvoke((MethodInvoker)delegate ()
            {
                //listBox1.Items.Add(sD.ReadLine() + "\n");
                disegna(sD.getDistDx(), sD.getDistSx(), sD.getOrientamento(), sD.getVelocita());
                disegnaBussola(sD.getOrientamento());

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
            drawPixel(gMap, trasla(pDraw, p));
        }

        public Point trasla(Panel panel, Point p)
        {

            Point ptW = new Point();
            ptW.X = p.X /** scala*/ + panel.Width / 2;
            ptW.Y = panel.Height / 2 - p.Y /* * scala*/;

            return ptW;
        }

        //Disegna la bussola 
        private void disegnaBussola(int orientamento)
        {
            //BUSSOLA
            bussola.CalcolaPunto(orientamento);
            Point center = new Point(pCompass.Width / 2, pCompass.Height / 2);
            Point compassPoint = trasla(pCompass, bussola.p);



            //Aggiorna il grado della bussola 
            lOrientamento.Text = orientamento.ToString() + "°";

            gComp.Clear(pCompass.BackColor);
            gComp.DrawImage(Properties.Resources.CompassRacing, new Point(0,0));
            
            gComp.DrawLine(pen, center, compassPoint);

            drawPixel(gComp, center);

            
        }
        private void disegna(int distDx, int distSx, int orientamento, int velocita)
        {

            map.add(distDx, distSx, orientamento, velocita); //Carattere 1 = dist da Dx - carattere 2 = dist da Sx - carattere 3 = angolo orienamento   
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
            sD.Write("START");           //prova
                                         //if (bt.getTesto() != "")
                                         //textBox1.Text = bt.getTesto();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //invio W quando viene premuto il tasto, TODO l'arudino capisce e si ferma
            sD.Write("STOP");
        }

        private void opzioniToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 frm = new Form2(comPort, status);
            frm.StartPosition = FormStartPosition.CenterScreen;
            DialogResult res = frm.ShowDialog();

            if (res == DialogResult.OK)
            {
                comPort = frm.getPort();
                openPort();
            }
            else if (res == DialogResult.Abort)
            {
                comPort = "";
                sD.DtrEnable = false;
                sD.Close();
                status = false;
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
                    status = true;
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
                lOrientamento.Text = sD.getOrientamento(riga).ToString() + "°";
                disegna(sD.getDistDx(riga), sD.getDistSx(riga), sD.getOrientamento(riga), sD.getVelocita(riga));
                disegnaBussola(sD.getOrientamento(riga));
            }
            f.Close();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }


        //Pulsante reset mappa
        private void button2_Click(object sender, EventArgs e)
        {
            gMap.Clear(pDraw.BackColor);
            map.reset();
        }
    }
}
