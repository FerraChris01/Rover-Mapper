using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rover
{

    //@author Peduzzi Samuele 
    class CMappa
    {
        //Attributi

        //Punto di partenza del rover (non necessario)
        //private Point pStart;

        //Memorizzazion punti a destra e a sinistra del drone
        //Punti da sostituire con una lista
        public Point[] pDx { get; }
        public Point[] pSx { get; }
        //Numero di coppie di punti memorizzate
        private int numEl;
        //Distanza dal punto di partenza
        private int distFromP; 
       
        //Metodi

        //Costruttore vuoto 
        public CMappa()
        {
            //pStart = new Point(0, 0);

            pDx = new Point[100];
            pSx = new Point[100];

            numEl = 0;
            distFromP = 0;
        }
        //Il sequente metodo permette di aggiungere due nuovi punti a destra e a sinistra mediamnte le due distanze
        public void add(int distanzaDx, int distanzaSx)
        {
            pDx[numEl] = new Point(distanzaDx, distFromP);
            pDx[numEl] = new Point(distanzaSx, distFromP);

            distFromP++; //Incremento distanza dal punto zero
            numEl++; //Incremento numero di punti a destra e sinistra
        }


        

    }
}
