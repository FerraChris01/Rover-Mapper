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

    }
}
