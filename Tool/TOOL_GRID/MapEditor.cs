using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    enum CursorCur
    {
        ICON,
        OBJECT,
        NONE
    }

    public partial class MapEditor : Form
    {
        Image imageCursor = null;
        CursorCur CurrentCursor;
        private List<Object> listObject;
        private Grid grid;

        Bitmap bmpMap;

        private int objectId;

        private int objectIndexInfo;

        private const int CELL_SIZE = 136;

        private const int START_INDEX = 0;

        int widthBackground, heightBackground;

        public MapEditor()
        {
            InitializeComponent();
            // set panel background
            panel1.AutoScroll = true;
            panel1.HorizontalScroll.Enabled = true;
            panel1.HorizontalScroll.Visible = true;

            // List Object
            listViewOB.LargeImageList = imageListOB;
            listViewOB.View = View.LargeIcon;

            for (int i = 0; i < imageListOB.Images.Count; i++)
            {
                listViewOB.Items.Add(imageListOB.Images.Keys[i], i);
            }

            //listViewOB.Items.Add("BrickOutCastle", 0);
            //listViewOB.Items.Add("BrickOutCastle", 0);
            //listViewOB.Items.Add("Torch", 1);
            //listViewOB.Items.Add("BrickSceneOne", 2);
            //listViewOB.Items.Add("Candle", 3);

            //imageListOB.TransparentColor = Color.Transparent;

            // other
            CurrentCursor = CursorCur.NONE;

            listObject = new List<Object>();
            if (listObject != null)
            {
                listObject.Clear();
            }

            tbCellSize.Text = CELL_SIZE + "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            // Set filter options and filter index.
            openFile.Filter = "PNG Files (*.png)|*.png|All Files (*.*)|*.*";
            openFile.FilterIndex = 1;
            openFile.Title = "Open file background";

            if (openFile.ShowDialog() == DialogResult.OK)
            {
                Image image = Image.FromFile(openFile.FileName);
                pictureBoxBG.Image = image;
                pictureBoxBG.SizeMode = PictureBoxSizeMode.AutoSize;

                textBoxBGWidth.Text = "     " + image.Size.Width.ToString() + " pixel";
                textBoxBGHeigth.Text = "     " + image.Size.Height.ToString() + " pixel";

                widthBackground = image.Size.Width;
                heightBackground = image.Size.Height;

                grid = new Grid();
                grid.CreateGrid(widthBackground, heightBackground, int.Parse(tbCellSize.Text));
                //MessageBox.Show(grid.NumXCells.ToString());

                bmpMap = new Bitmap(pictureBoxBG.Image);
            }
        }

        private void listViewOB_MouseClick(object sender, MouseEventArgs e)
        {
            textBoxNameOB.Visible = true;
            CurrentCursor = CursorCur.OBJECT;
            resetObjInfo();

            // Lay image khi click + doi cursor          
            //foreach (ListViewItem itm in listViewOB.SelectedItems)
            //{
            //    int imgIndex = itm.ImageIndex;
            //    if (imgIndex >= 0 && imgIndex < this.imageListOB.Images.Count)
            //    {
            //        imageCursor = this.imageListOB.Images[imgIndex];
            //        switch (imgIndex)
            //        {
            //            case 0:
            //            case 1:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 16, 32);
            //                break;
            //            case 2:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 8, 16);
            //                break;
            //            case 3:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 24, 48);
            //                break;
            //            case 4:
            //            case 5:
            //            case 8:
            //            case 9:
            //            case 10:
            //            case 11:
            //            case 12:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 16, 16);
            //                break;
            //            case 6:
            //            case 7:
            //            case 13:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 8, 8);
            //                break;
            //            case 14:
            //                imageCursor = Utilities.ResizeImage(imageCursor, 15, 14);
            //                break;

            //        }
            //    }
            //}
            int imgIndex = listViewOB.SelectedItems[0].ImageIndex;
            string name = listViewOB.SelectedItems[0].Text;
            imageCursor = this.imageListOB.Images[imgIndex];

            switch (name)
            {
                case "Simon":
                case "Torch":
                case "Zombie":
                case "FishMan":
                case "BlackKnight":
                    imageCursor = Utilities.ResizeImage(imageCursor, 16, 32);
                    break;
                case "Candle":
                    imageCursor = Utilities.ResizeImage(imageCursor, 8, 16);
                    break;
                case "Gate":
                    imageCursor = Utilities.ResizeImage(imageCursor, 24, 48);
                    break;
                case "BoundingMap":
                case "Portal":
                case "Ground":
                case "Whip":
                case "Money":
                case "Ball":
                case "SmallHeart":
                    imageCursor = Utilities.ResizeImage(imageCursor, 16, 16);
                    break;
                case "BottomStair":
                case "TopStair":
                case "Heart":
                    imageCursor = Utilities.ResizeImage(imageCursor, 8, 8);
                    break;
                case "Knife":
                case "Axe":
                case "Boomerang":
                    imageCursor = Utilities.ResizeImage(imageCursor, 15, 14);
                    break;
                case "Crown":
                    imageCursor = Utilities.ResizeImage(imageCursor, 15, 16);
                    break;
                case "BlackLeopard":
                    imageCursor = Utilities.ResizeImage(imageCursor, 24, 15);
                    break;
                case "VampireBat":
                    imageCursor = Utilities.ResizeImage(imageCursor, 12, 14);
                    break;

            }
            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            textBoxHeightOB.Text = imageCursor.Height.ToString();
            textBoxWidthOB.Text = imageCursor.Width.ToString();
            textBoxNameOB.Text = name;
            objectId = imgIndex + 1;
        }

        private void pictureBoxBG_MouseMove(object sender, MouseEventArgs e)
        {
            MouseEventArgs me = (MouseEventArgs)e;
            Point coordinates = me.Location;
            if (pictureBoxBG.Image != null)
            {
                if (this.imageCursor == null)
                {
                    textBoxX.Text = "na";
                    textBoxY.Text = "na";
                }
                else
                {
                    // toa do top - left
                    if (coordinates.X - imageCursor.Width / 2 >= 0 && coordinates.Y - imageCursor.Height / 2 >= 0
                        && coordinates.X + imageCursor.Width / 2 <= pictureBoxBG.Width && coordinates.Y + imageCursor.Height / 2 <= pictureBoxBG.Height)
                    {
                        textBoxX.Text = (coordinates.X - imageCursor.Width / 2).ToString();
                        textBoxY.Text = (coordinates.Y - imageCursor.Height / 2).ToString();
                    }
                    else
                    {
                        textBoxX.Text = "x";
                        textBoxY.Text = "y";
                    }
                }
            }
        }

        private void pictureBoxBG_Click(object sender, EventArgs e)
        {
            if (CurrentCursor == CursorCur.OBJECT)
            {
                if (textBoxX.Text.Trim() != "x" && textBoxY.Text.Trim() != "y")
                {
                    // them hinh anh vao pictureBox           
                    MouseEventArgs me = (MouseEventArgs)e;
                    Point coordinates = me.Location;
                    PictureBox p = new PictureBox();
                    p.Image = imageCursor;
                    p.Location = new Point(me.Location.X - imageCursor.Width / 2, me.Location.Y - imageCursor.Height / 2);
                    p.SizeMode = PictureBoxSizeMode.AutoSize;
                    p.BackColor = Color.Transparent;

                    // them vao list  
                    string nameOb = textBoxNameOB.Text.Trim();

                    Object ob = new Object(p, nameOb, Convert.ToInt32(textBoxX.Text.Trim()), Convert.ToInt32(textBoxY.Text.Trim()), p.Width, p.Height);

                    listObject.Add(ob);
                    listObject.ElementAt(listObject.Count - 1).Pic.Click += new System.EventHandler(PictureBoxes_Click);
                    listObject.ElementAt(listObject.Count - 1).Pic.MouseMove += new System.Windows.Forms.MouseEventHandler(PictureBoxes_MouseMove);
                    listObject.ElementAt(listObject.Count - 1).Pic.MouseLeave += new System.EventHandler(PictureBoxes_MouseLeave);

                    pictureBoxBG.Controls.Add(listObject.ElementAt(listObject.Count - 1).Pic);

                    drawImage(p);
                }
                else
                {
                    MessageBox.Show("Don't have background!");
                }
            }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            if (listObject.Count > 0)
            {
                using (var folderBrowser = new OpenFileDialog())
                {
                    folderBrowser.ValidateNames = false;
                    folderBrowser.CheckFileExists = false;
                    folderBrowser.CheckPathExists = true;
                    // Always default to Folder Selection.
                    folderBrowser.FileName = "Folder Selection.";
                    if (folderBrowser.ShowDialog() == DialogResult.OK)
                    {
                        string folderPath = Path.GetDirectoryName(folderBrowser.FileName);
                        grid.clearObject();
                        for (int i = 0; i < listObject.Count; i++)
                            grid.AddObjToCell(listObject[i], i);

                        Utilities.WriteFileTxTObj(folderPath, listObject);
                        Utilities.WriteFileTxtGrid(folderPath, grid);
                        MessageBox.Show("Save successfully!");
                    }
                }
            }
            else
            {
                MessageBox.Show("No object in background!");
            }
        }

        private void pictureBoxBG_MouseLeave(object sender, EventArgs e)
        {
            textBoxX.Text = "x";
            textBoxY.Text = "y";

        }

        // click vo picbox new tren background
        private void PictureBoxes_Click(object sender, EventArgs e)
        {
            if (CurrentCursor == CursorCur.ICON)
            {
                // xoa pic tren background va list
                PictureBox p = (PictureBox)sender;

                for (int i = 0; i < listObject.Count; i++)
                {
                    if (listObject.ElementAt(i).Pic == p)
                    {
                        pictureBoxBG.Controls.Remove(listObject.ElementAt(i).Pic);
                        listObject.RemoveAt(i);
                        break;
                    }
                }
            }
            else if (CurrentCursor == CursorCur.NONE)
            {
                PictureBox p = (PictureBox)sender;

                for (int i = 0; i < listObject.Count; i++)
                {
                    if (listObject.ElementAt(i).Pic == p)
                    {
                        objectIndexInfo = i;

                        string id = listObject.ElementAt(i).Id.ToString();
                        string name = listObject.ElementAt(i).Name;
                        int posX = (int)listObject.ElementAt(i).PosX;
                        int posY = (int)listObject.ElementAt(i).PosY;
                        int w = listObject.ElementAt(i).Width;
                        int h = listObject.ElementAt(i).Height;
                        int sceneId = 0;

                        if (listObject.ElementAt(i).Id == 14)
                        {
                            sceneId = listObject.ElementAt(i).AniSetId;
                            numObjDelay.Enabled = true;
                        }
                        else
                        {
                            numObjDelay.Enabled = false;
                        }

                        setOjectInfo(id, name, posX, posY, w, h, sceneId);

                        break;
                    }
                }
            }
        }

        private void resetObjInfo()
        {
            objectIndexInfo = -1;
            setOjectInfo("", "", 0, 0, 0, 0, 0);
        }

        private void setOjectInfo(string id, string name, int posX, int posY, int w, int h, int sceneId)
        {
            tbObjId.Text = id;
            tbObjName.Text = name;
            numX.Value = posX;
            numY.Value = posY;
            numWidth.Value = w;
            numHeight.Value = h;
            numObjDelay.Value = sceneId;
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            //grid.clearObject();
            //for (int i = 0; i < listObject.Count; i++)
            //    grid.AddObjToCell(listObject[i], i);

            //Utilities.WriteFileTxTObj(saveFileDialog1, listObject);
            //Utilities.WriteFileTxtGrid(saveFileDialog1, grid);
            //MessageBox.Show("Save successfully!");
        }

        private void PictureBoxes_MouseMove(object sender, EventArgs e)
        {
            if (CurrentCursor != CursorCur.OBJECT)
            {
                this.Cursor = Cursors.Hand;
            }
        }

        private void PictureBoxes_MouseLeave(object sender, EventArgs e)
        {
            if (imageCursor != null)
                this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            else
                this.Cursor = Cursors.Default;
        }

        private void cancelPic_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;
            CurrentCursor = CursorCur.NONE;
            imageCursor = null;
            resetObjInfo();
        }

        private void removePic_Click(object sender, EventArgs e)
        {
            imageCursor = this.removePic.Image;
            imageCursor = Utilities.ResizeImage(imageCursor, 8, 8);
            CurrentCursor = CursorCur.ICON;
            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            resetObjInfo();
        }

        private void buttonSaveImg_Click(object sender, EventArgs e)
        {
            saveImgFileDialog.Filter = "Image Files (*.png)|*.png|All files (*.*)|*.*";
            saveImgFileDialog.FilterIndex = 1;
            saveImgFileDialog.ShowDialog();
        }

        private void saveImgFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveImgFileDialog.FileName),
            System.IO.Path.GetFileName(saveImgFileDialog.FileName));

            ImageCodecInfo myImageCodecInfo = GetEncoderInfo("image/jpeg");
            System.Drawing.Imaging.Encoder myEncoder;
            EncoderParameter myEncoderParameter;
            EncoderParameters myEncoderParameters = new EncoderParameters(1);

            myEncoder = System.Drawing.Imaging.Encoder.Quality;
            myEncoderParameter = new EncoderParameter(myEncoder, 100L); // 100% img quality
            myEncoderParameters.Param[0] = myEncoderParameter;

            //pictureBoxBG.Image.Save(@path, ImageFormat.Jpeg);
            //bmpMap.Save(@path, ImageFormat.Jpeg);
            bmpMap.Save(@path, myImageCodecInfo, myEncoderParameters);
            MessageBox.Show("Save image successfully!");
        }

        private static ImageCodecInfo GetEncoderInfo(String mimeType)
        {
            int j;
            ImageCodecInfo[] encoders;
            encoders = ImageCodecInfo.GetImageEncoders();
            for (j = 0; j < encoders.Length; ++j)
            {
                if (encoders[j].MimeType == mimeType)
                    return encoders[j];
            }
            return null;
        }

        private Image getImageByName(string name)
        {
            int imgIndex = getImageIndexByName(name);
            Image image = this.imageListOB.Images[imgIndex];
            //if (imgIndex == 0)
            //{
            //    image = Utilities.ResizeImage(image, 32, 64);
            //}
            //else if (imgIndex == 1)
            //{
            //    image = Utilities.ResizeImage(image, 32, 32);
            //}
            //else if (imgIndex == 2)
            //{
            //    image = Utilities.ResizeImage(image, 32, 32);
            //}
            //else if (imgIndex == 3)
            //{
            //    image = Utilities.ResizeImage(image, 32, 64);
            //}
            return image;
        }

        private int getImageIndexByName(string name)
        {
            int imgIndex = 0;

            for (int i = 0; i < imageListOB.Images.Count; i++)
            {
                if (imageListOB.Images.Keys[i].Equals(name))
                {
                    return i;
                }
            }

            return imgIndex;
        }

        private void drawImage(PictureBox p)
        {
            Image imgObj = p.Image;
            using (Graphics graphic = Graphics.FromImage(bmpMap))
            {
                graphic.DrawImage(imgObj, p.Location.X, p.Location.Y);
            }
        }

        private void renderListImage()
        {
            if (listObject.Count > 0)
            {
                for (int i = 0; i < listObject.Count; i++)
                {
                    drawImage(listObject.ElementAt(i).Pic);
                }
            }
        }

        private void btnChangeCellSize_Click(object sender, EventArgs e)
        {
            if (textBoxX.Text.Trim() != "x" && textBoxY.Text.Trim() != "y")
            {
                grid.CreateGrid(widthBackground, heightBackground, int.Parse(tbCellSize.Text));
            }
            else
            {
                MessageBox.Show("Don't have background!");
            }
        }

        private void btnLoadObject_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            // Set filter options and filter index.
            openFile.Filter = "Text Files (*.txt)|*.txt|All files (*.*)|*.*";
            openFile.FilterIndex = 1;
            openFile.Title = "Load object from file";

            if (openFile.ShowDialog() == DialogResult.OK)
            {
                string[] lines = System.IO.File.ReadAllLines(openFile.FileName);
                string[] infos;
                Object obj;
                PictureBox p;
                int posX, posY, width, height, sceneId;
                int id;
                string name;

                clearAllPictureBox();
                foreach (string line in lines)
                {
                    if (line.StartsWith("#") || line.StartsWith("//")) continue;
                    infos = line.Split(' ');

                    if (infos.Length == 1)
                    {
                        infos = line.Split('\t');
                    }

                    name = infos[2];
                    posX = int.Parse(infos[3]);
                    posY = int.Parse(infos[4]);
                    width = int.Parse(infos[5]);
                    height = int.Parse(infos[6]);

                    if (infos.Length > 6)
                    {
                        sceneId = int.Parse(infos[7]);
                    }
                    else
                    {
                        sceneId = 0;
                    }

                    if (int.TryParse(infos[1], out id))
                    {
                        p = new PictureBox();
                        p.Image = Utilities.ResizeImage(getImageByName(name), width, height);
                        p.Location = new Point(posX, posY);
                        p.SizeMode = PictureBoxSizeMode.AutoSize;
                        p.BackColor = Color.Transparent;

                        obj = new Object(p, name, posX, posY, width, height, sceneId);

                        listObject.Add(obj);
                        listObject.ElementAt(listObject.Count - 1).Pic.Click += new System.EventHandler(PictureBoxes_Click);
                        listObject.ElementAt(listObject.Count - 1).Pic.MouseMove += new System.Windows.Forms.MouseEventHandler(PictureBoxes_MouseMove);
                        listObject.ElementAt(listObject.Count - 1).Pic.MouseLeave += new System.EventHandler(PictureBoxes_MouseLeave);
                        pictureBoxBG.Controls.Add(listObject.ElementAt(listObject.Count - 1).Pic);
                    }

                }
                renderListImage();
            }
        }

        private void numObjDelay_ValueChanged(object sender, EventArgs e)
        {
            if (objectIndexInfo != -1)
            {
                if (listObject.ElementAt(objectIndexInfo).Id == 14)
                {
                    listObject.ElementAt(objectIndexInfo).AniSetId = (int)numObjDelay.Value;
                }
            }
        }

        private void numWidth_ValueChanged(object sender, EventArgs e)
        {
            if (objectIndexInfo != -1)
            {
                listObject.ElementAt(objectIndexInfo).Width = (int)numWidth.Value;
            }
        }

        private void numHeight_ValueChanged(object sender, EventArgs e)
        {
            if (objectIndexInfo != -1)
            {
                listObject.ElementAt(objectIndexInfo).Height = (int)numHeight.Value;
            }
        }

        private void numX_ValueChanged(object sender, EventArgs e)
        {
            if (objectIndexInfo != -1)
            {
                listObject.ElementAt(objectIndexInfo).PosX = (int)numX.Value;
            }
        }

        private void numY_ValueChanged(object sender, EventArgs e)
        {
            if (objectIndexInfo != -1)
            {
                listObject.ElementAt(objectIndexInfo).PosY = (int)numY.Value;
            }
        }

        private void clearAllPictureBox()
        {
            if (listObject.Count > 0)
            {
                for (int i = 0; i < listObject.Count; i++)
                {
                    pictureBoxBG.Controls.Remove(listObject.ElementAt(i).Pic);
                }
            }
        }

        //private void buttonRest_Click(object sender, EventArgs e)
        //{
        //    imageCursor = null;
        //    CurrentCursor = CursorCur.NONE;
        //    if (listObject.Count > 0)
        //    {
        //        for (int i = 0; i < listObject.Count; i++)
        //        {
        //            pictureBoxBG.Controls.Remove(listObject.ElementAt(i).Pic);
        //        }
        //    }
        //    listObject.Clear();

        //    pictureBoxBG.Image = null;
        //}
    }
}
