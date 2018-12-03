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
        public  float X { get; set; }
        public  float Y { get; set; }
        public  int orientamento { get; set; }


        
        public float getRadianti(int gradi) 
        {
            return (gradi * (float)(Math.PI / 180));
        }


        //Metodi
        public CRover()
        {
            X = 0;
            Y = 0;
            orientamento = 0;

        }

        public void calcSpostamento(int o)
        {
            X += (float)Math.Cos(getRadianti(o));
            Y += (float)Math.Sin(getRadianti(o));
            orientamento = o;
        }

    }
}
