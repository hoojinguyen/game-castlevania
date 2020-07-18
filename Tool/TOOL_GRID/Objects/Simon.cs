using System.Windows.Forms;

namespace MapEditor.Objects
{
    public class Simon : Object
    {
        public int Direction { get; set; }
        public int State { get; set; }

        public Simon(int direction, int state, PictureBox Pic, string name, int PosX, int PosY,
            int Width = 0, int Height = 0, int sceneId = 1, int itemType = -2) :
            base(Pic, name, PosX, PosY, Width, Height, sceneId, itemType)
        {
            this.Direction = direction;
            this.State = state;
        }

        public override string toObjectStr()
        {
            string str = base.toObjectStr() + " " + Direction + " " + State;
            return str;
        }
    }
}
