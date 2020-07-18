using System.Windows.Forms;

namespace MapEditor.Objects
{
    public class Portal : Object
    {
        public int Position { get; set; }
        public Portal(int position, PictureBox Pic, string name, int PosX, int PosY,
            int Width = 0, int Height = 0, int sceneId = 1, int itemType = -2) :
            base(Pic, name, PosX, PosY, Width, Height, sceneId, itemType)
        {
            this.Position = position;
        }

        public override string toObjectStr()
        {
            string str = base.toObjectStr() + " " + Position;
            return str;
        }
    }
}
