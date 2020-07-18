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

        public int itemType { get; set; }

        public Object(PictureBox Pic, string name, int PosX, int PosY, int Width = 0,
            int Height = 0, int sceneId = 1, int itemType = -2)
        {
            this.Pic = Pic;
            this.itemType = itemType;
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
                AniSetId = 32;
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
                AniSetId = sceneId;
            }
            else if (this.Name == "TopStair")
            {
                Id = 16;
                AniSetId = sceneId;
            }
            else if (this.Name == "Ground")
            {
                Id = 17;
                AniSetId = -1;
            }
            else if (this.Name == "MovingPlatform")
            {
                Id = 18;
                AniSetId = 33;
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
            else if (this.Name == "Knife")
            {
                Id = 103;
                AniSetId = 40;
            }
            else if (this.Name == "Axe")
            {
                Id = 104;
                AniSetId = 40;
            }
            else if (this.Name == "Boomerang")
            {
                Id = 105;
                AniSetId = 40;
            }
            else if (this.Name == "Crown")
            {
                Id = 106;
                AniSetId = 40;
            }
            //Enemy
            else if (this.Name == "Zombie")
            {
                Id = 200;
                AniSetId = 70;
            }
            else if (this.Name == "BlackLeopard")
            {
                Id = 201;
                AniSetId = 71;
            }
            else if (this.Name == "VampireBat")
            {
                Id = 202;
                AniSetId = 72;
            }
            else if (this.Name == "FishMan")
            {
                Id = 203;
                AniSetId = 73;
            }
            else if (this.Name == "BlackKnight")
            {
                Id = 204;
                AniSetId = 74;
            }
            else if (this.Name == "Ghost")
            {
                Id = 205;
                AniSetId = 75;
            }
            else if (this.Name == "Fleamen")
            {
                Id = 206;
                AniSetId = 76;
            }
            else if (this.Name == "Skeleton")
            {
                Id = 207;
                AniSetId = 77;
            }
            else if (this.Name == "Raven")
            {
                Id = 208;
                AniSetId = 78;
            }
            else if (this.Name == "PhantomBat")
            {
                Id = 300;
                AniSetId = 80;
            }

            this.PosX = PosX;
            this.PosY = PosY;
            this.Width = Width;
            this.Height = Height;
        }

        public virtual string toObjectStr()
        {
            string str = Id + " " + Name + " " + PosX + " " + PosY + " " + Width + " " + Height + " " + AniSetId + " " + itemType;

            return str;
        }
    }
}
