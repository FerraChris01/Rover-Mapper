﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rover
{

    

    public partial class Form1 : Form
    {
        //Attributi 

        //Porta seriale al solo scopo di test (Broch la sostituirà con la lettura via bluetooth)
        private SerialPort bt;
        //Classe per la gestionde della mappa
        CMappa map;
        //Drawing class
        Graphics g;
        Pen pen;
        Brush b = (Brush)Brushes.Black;

        //Metodi
        //Utilizzare questo metodo per disegnare un punto
        private void drawPoint(Point p)
        {
            g.FillRectangle(b, p.X, p.Y , 2, 2);
        }

        //Costruttore
        public Form1()
        {
            //Inizializzazione componenti grafiche 
            InitializeComponent();

            map = new CMappa();
            g = pDraw.CreateGraphics();
            pen = new Pen(Color.Red);

            //Porta seriale da sostituire con comunicazione bluetooth !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //https://social.msdn.microsoft.com/Forums/vstudio/en-US/92888551-10c7-4bde-86f3-3445d9293ada/bluetooth-communication-using-serial-ports?forum=csharpgeneral
            //Creazione porta seriale per bluetooth 
            bt = new SerialPort("COM4", 38400);

            bt.DataReceived += bt_DataReceived;
            bt.Open();

            


        }
        //Ogni volta che si ricevono dati da arduino
        private void bt_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
           String line = bt.ReadLine();
            //float dx = s.ReadLine().Substring(0,2);
            //float sx =  s.ReadLine().Substring(3, 5);
            //map.add(dx, sx); //--> da sistemare
            this.BeginInvoke((MethodInvoker)delegate ()
            {
                textBox1.Text += line;
            });

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void bStart_Click(object sender, EventArgs e)
        {
            //invio S quando viene premuto il tasto, TODO l'arudino capisce e starta
            //bt.Write("S");
                                    
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //invio W quando viene premuto il tasto, TODO l'arudino capisce e si ferma
            //bt.Write("W");
        }
    }
}
