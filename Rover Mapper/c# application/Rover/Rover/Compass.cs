using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//@authors Peduzzi, Mauri
namespace Rover
{
    public class Compass
    {
       public Point p { get; set; }
       
        public Compass()
        {
            p = new Point(0, 0);
        }

        public void CalcolaPunto(int gradi)
        {
            int x = (int)(100 * (Math.Cos(getRadianti(gradi))));
            int y = (int)(100 * (Math.Sin(getRadianti(gradi))));
            p = new Point(x , y);
        }

        private float getRadianti(int gradi)
        {
            return (gradi * (float)(Math.PI / 180.0F));
        }

    }
}
