using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public class Object
    {
        public int Id { get; set; }

        public int AniSetId { get; set; }

        public string Name { get; set; }

        public float PosX { get; set; }

        public float PosY { get; set; }

        public int Width { get; set; }

        public int Height { get; set; }

        public PictureBox Pic { get; set; }

        public int delay { get; set; }

        public Object(PictureBox Pic, string name, int PosX, int PosY, int Width = 0, int Height = 0, int sceneId = 1)
        {
            this.Pic = Pic;
            this.delay = delay;
            this.Name = name;
            if (this.Name == "Simon")
            {
                Id = 1;
                AniSetId = 1;
            }
            //map object
            else if (this.Name == "Torch")
            {
                Id = 10;
                AniSetId = 30;
            }
            else if (this.Name == "Candle")
            {
                Id = 11;
                AniSetId = 31;
            }
            else if (this.Name == "Gate")
            {
                Id = 12;
                AniSetId = 31;
            }
            else if (this.Name == "BoundingMap")
            {
                Id = 13;
                AniSetId = -1;
            }
            else if (this.Name == "Portal")
            {
                Id = 14;
                AniSetId = sceneId;
            }
            else if (this.Name == "BottomStair")
            {
                Id = 15;
                AniSetId = -1;
            }
            else if (this.Name == "TopStair")
            {
                Id = 16;
                AniSetId = -1;
            }
            //item
            else if (this.Name == "Whip")
            {
                Id = 100;
                AniSetId = 40;
            }
            else if (this.Name == "SmallHeart")
            {
                Id = 101;
                AniSetId = 40;
            }
            else if (this.Name == "Heart")
            {
                Id = 102;
                AniSetId = 40;
            }



            this.PosX = PosX;
            this.PosY = PosY;
            this.Width = Width;
            this.Height = Height;
        }

        public string toObjectStr()
        {
            string str = Id + " " + Name + " " + PosX + " " + PosY + " " + Width + " " + Height + " " + AniSetId;
            return str;
        }
    }
}
