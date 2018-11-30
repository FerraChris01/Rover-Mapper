using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rover
{
    class Bluetooth
    {
        private SerialPort sp;
        //String[] buffer;
        String testo;

        public Bluetooth()
        {
            //buffer = new String[5];
            testo = "";
            sp = new SerialPort("COM5", 9600);
            sp.Open();
            sp.DataReceived += Sp_DataReceived;
        }

        private void Sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                //testo=sp.ReadLine();
                testo = leggiSeriale();
            }
            catch
            {
                new Exception("Nessun valore, buggato");
            }
        }

        public void inviaSeriale(String s)
        {
            sp.Write(s);
        }

        public String leggiSeriale()
        {
            return sp.ReadLine();
        }

        public String getTesto()
        {
            return testo;
        }


        //metodo che cerca nel testo il prossimo carattere a capo,
        //se lo trova vuol dire che il numero finisce li

        private int getNextNumber(int j)
        {
            int distance = 0;
            bool found = false;
            for (int i = j; found == false || i > 100; i++)
            {
                if (testo.ElementAt(i) == '\n')
                {
                    found = true;
                    distance = i - j;
                }
            }
            return distance;
        }


        //i prossimi 3 metodi DOVREBBERO dare direttamente le misure degli ultrasuoni 
        //con tutti i controlli


        public int getFr()
        {
            String fr = "";
            bool found = false;
            if (testo != "")
            {
                for (int i = 0; i < testo.Length || found == false; i++)
                {
                    if (testo.ElementAt(i) == 'f')
                    {
                        fr = testo.Substring(i, getNextNumber(i));
                        found = true;
                    }

                }

            }
            return Int32.Parse(fr);
        }



        public int getDX()
        {
            String dx = "";
            bool found = false;
            if (testo != "")
            {
                for (int i = 0; i < testo.Length || found == false; i++)
                {
                    if (testo.ElementAt(i) == 'd')
                    {
                        dx = testo.Substring(i, getNextNumber(i));
                        found = true;
                    }

                }

            }
            return Int32.Parse(dx);
        }

        public int getSX()
        {
            String sx = "";
            bool found = false;
            if (testo != "")
            {
                for (int i = 0; i < testo.Length || found == false; i++)
                {
                    if (testo.ElementAt(i) == 's')
                    {
                        sx = testo.Substring(i, getNextNumber(i));
                        found = true;
                    }

                }

            }
            return Int32.Parse(sx);
        }
    }
}
