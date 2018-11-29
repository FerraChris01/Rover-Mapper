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

        //Classe utilizzata per la memorizzazione della posizione del rover 
        CRover rover;

        //Memorizzazion punti a destra e a sinistra del drone
        //Punti da sostituire con una lista
        public List<Point> pDx { get; }
        public List<Point> pSx { get; }

        //Distanza dal punto di partenza
        //private int distFromP;

        //Metodi

        //Costruttore vuoto 
        public CMappa()
        {
            //pStart = new Point(0, 0);
            rover = new CRover();

            pDx = new List<Point>(100);
            pSx = new List<Point>(100);

            //distFromP = 0;
        }
        //Il sequente metodo permette di aggiungere due nuovi punti a destra e a sinistra mediamnte le due distanze
        public void add(int distanzaDx, int distanzaSx, int orientamento)
        {

            //I CALCOLI IN QUESTO METODO VANNO FATTI CONSIDERANDO IL PIANO TRADIZIONALE (Il form si occuperà di invertire la y)


            //if (orientamento == SUD)
            pDx.Add(new Point(distanzaDx, rover.Y));
            pSx.Add(new Point((distanzaDx + distanzaSx), rover.Y));
            rover.Y++; ; //L'ordinata viene decrementata, difatti il rover si sposta verso il basso




            //else if (orientamento == NORD)   
            //pDx.Add(new Point(distanzaDx, distFromP));
            //pSx.Add(new Point((distanzaDx + distanzaSx), distFromP));
            //distFromP++; //L'ordinata viene decrementata, difatti il rover si sposta verso il basso

            //else if (orientamento == OVEST)   

            //else if (orientamento == EST)   


        }




    }
}
