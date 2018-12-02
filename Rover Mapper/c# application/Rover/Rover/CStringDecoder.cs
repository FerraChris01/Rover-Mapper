using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rover
{
    //@author Peduzzi, Broch

    //Classe che permette la decodifica della stringa in formato csv
    //Accetta come input sia una stringa letta salla seriale, sia una stringa passata come parametro

    class CStringDecoder : SerialPort
    {


        //Attributi
        public string riga { get; set; }
        private string[] campi;

        //Metodi

        private int calc(String val)
        {
            int dist = 0;

            int.TryParse(val, out dist);

            return dist;
        }

        public CStringDecoder()
        {
            PortName = "COM5";
            BaudRate = 9600;
        }
        public CStringDecoder(string PortName, int BaudRate)
        {
            this.PortName = PortName;
            this.BaudRate = BaudRate;
        }
        
        public void leggiRiga()
        {
            riga = ReadLine();
            campi = riga.Split(';');
        }

        public int getDistDx()
        {
            return calc(campi[0]);
        }

        public int getDistDx(String strdaDecod)
        {
            return calc(strdaDecod.Split(';')[0]);
        }

        public int getDistSx()
        {
            return calc(campi[1]);
        }

        public int getDistSx(String strdaDecod)
        {
            return calc(strdaDecod.Split(';')[1]);
        }

        public int getOrientamento()
        {
            return calc(campi[2]);
        }

        public int getOrientamento(String strdaDecod)
        {
            return calc(strdaDecod.Split(';')[2]);
        }


    }

}


//public void inviaSeriale(String s)
//{
//    sp.Write(s);
//}

//public String leggiSeriale()
//{
//    return sp.ReadLine();
//}

//public String getTesto()
//{
//    return testo;
//}


//metodo che cerca nel testo il prossimo carattere a capo,
//se lo trova vuol dire che il numero finisce li

//        private int getNextNumber(int j)
//        {
//            int distance = 0;
//            bool found = false;
//            for (int i = j; found == false || i > 100; i++)
//            {
//                if (testo.ElementAt(i) == '\n')
//                {
//                    found = true;
//                    distance = i - j;
//                }
//            }
//            return distance;
//        }


//        //i prossimi 3 metodi DOVREBBERO dare direttamente le misure degli ultrasuoni 
//        //con tutti i controlli


//        public int getFr()
//        {
//            String fr = "";
//            bool found = false;
//            if (testo != "")
//            {
//                for (int i = 0; i < testo.Length || found == false; i++)
//                {
//                    if (testo.ElementAt(i) == 'f')
//                    {
//                        fr = testo.Substring(i, getNextNumber(i));
//                        found = true;
//                    }

//                }

//            }
//            return Int32.Parse(fr);
//        }



//        public int getDX()
//        {
//            String dx = "";
//            bool found = false;
//            if (testo != "")
//            {
//                for (int i = 0; i < testo.Length || found == false; i++)
//                {
//                    if (testo.ElementAt(i) == 'd')
//                    {
//                        dx = testo.Substring(i, getNextNumber(i));
//                        found = true;
//                    }

//                }

//            }
//            return Int32.Parse(dx);
//        }

//        public int getSX()
//        {
//            String sx = "";
//            bool found = false;
//            if (testo != "")
//            {
//                for (int i = 0; i < testo.Length || found == false; i++)
//                {
//                    if (testo.ElementAt(i) == 's')
//                    {
//                        sx = testo.Substring(i, getNextNumber(i));
//                        found = true;
//                    }

//                }

//            }
//            return Int32.Parse(sx);
//        }
//    }
//}
