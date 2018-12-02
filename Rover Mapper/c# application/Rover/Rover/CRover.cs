using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rover
{

    //author Peduzzi Samuele
    class CRover
    {
        //Attributi
        public  int X { get; set; }
        public  int Y { get; set; }
        public  int orientamento { get; set; }


        
        //Metodi
        public CRover()
        {
            X = 0;
            Y = 0;
            orientamento = 0;

        }

        public void Avanti(int o)
        {
            X += (int)Math.Cos(o);
            Y += (int)Math.Sin(o);
            orientamento = o;
        }

    }
}
