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
        public float X { get; set; }
        public float Y { get; set; }
        public int orientamento { get; set; }

        public int velocita { get; set; }

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
            velocita = 1;
        }

        public void calcSpostamento(int o, int velocita)
        {
            X += (float)Math.Cos(getRadianti(o)) * velocita;
            Y += (float)Math.Sin(getRadianti(o)) * velocita;
            orientamento = o;
            this.velocita = velocita;
        }

    }
}
