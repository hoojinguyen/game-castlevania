using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    class Utilities
    {
        // ghi file txt toa do obj trong map
        public static void WriteFileTxTObj(string SelectedPath, List<Object> listObj)
        {
            string path = SelectedPath + "/object.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);
            sWriter.WriteLine("#id\ttype\tname\tx\ty\twidth\theight\tani_set_id");
            for (int i = 0; i < listObj.Count; i++)
            {
                sWriter.WriteLine(i + " " + listObj.ElementAt(i).toObjectStr());
            }

            sWriter.Flush();
            sWriter.Close();
        }

        // ghi file txt cac obj trong tung cell cua grid
        public static void WriteFileTxtGrid(string SelectedPath, Grid grid)
        {
            string path = SelectedPath + "/grid.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);

            sWriter.WriteLine("[SETTINGS]");
            sWriter.WriteLine("#cell_size\tnum_x_cells\tnum_y_cells");
            sWriter.WriteLine(grid.cellSize + " " + grid.NumXCells + " " + grid.numYCells);

            sWriter.WriteLine("[OBJECTS]");
            sWriter.WriteLine("#index_x\tindex_y\tobject_id_1\tobject_id_2... \tobject_id_n");
            Cell cell;
            for (int i = 0; i < grid.numXCells; i++)
            {
                for (int j = 0; j < grid.numYCells; j++)
                {
                    cell = grid.listCells[i, j];
                    string strObj = "";
                    for (int k = 0; k < cell.listIdObj.Count; k++)
                    {
                        strObj += " " + cell.listIdObj[k].ToString();
                    }
                    sWriter.WriteLine(i + " " + j + strObj);
                }

            }
            sWriter.WriteLine("END");

            sWriter.Flush();
            sWriter.Close();

        }

        // resize img
        public static Bitmap ResizeImage(Image image, int rWidth, int rHeight)
        {
            var newImg = new Bitmap(rWidth, rHeight);
            Graphics.FromImage(newImg).DrawImage(image, 0, 0, rWidth, rHeight);
            Bitmap bmp = new Bitmap(newImg);
            return bmp;
        }
    }
}
