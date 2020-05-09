namespace MapEditor
{
    partial class MapEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapEditor));
            this.buttonLoad = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBoxBG = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxNameOB = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxHeightOB = new System.Windows.Forms.TextBox();
            this.textBoxWidthOB = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.listViewOB = new System.Windows.Forms.ListView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxBGWidth = new System.Windows.Forms.TextBox();
            this.textBoxBGHeigth = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.imageListOB = new System.Windows.Forms.ImageList(this.components);
            this.buttonSave = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.cancelPic = new System.Windows.Forms.PictureBox();
            this.removePic = new System.Windows.Forms.PictureBox();
            this.buttonSaveImg = new System.Windows.Forms.Button();
            this.saveImgFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.btnLoadObject = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnChangeCellSize = new System.Windows.Forms.Button();
            this.tbCellSize = new System.Windows.Forms.TextBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.numY = new System.Windows.Forms.NumericUpDown();
            this.numX = new System.Windows.Forms.NumericUpDown();
            this.numHeight = new System.Windows.Forms.NumericUpDown();
            this.numWidth = new System.Windows.Forms.NumericUpDown();
            this.tbObjId = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.numObjDelay = new System.Windows.Forms.NumericUpDown();
            this.label13 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.tbObjName = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBG)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cancelPic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.removePic)).BeginInit();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numObjDelay)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(13, 8);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(113, 23);
            this.buttonLoad.TabIndex = 1;
            this.buttonLoad.Text = "Load Background";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.pictureBoxBG);
            this.panel1.Location = new System.Drawing.Point(13, 60);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(985, 514);
            this.panel1.TabIndex = 2;
            // 
            // pictureBoxBG
            // 
            this.pictureBoxBG.Location = new System.Drawing.Point(-1, 3);
            this.pictureBoxBG.Name = "pictureBoxBG";
            this.pictureBoxBG.Size = new System.Drawing.Size(970, 506);
            this.pictureBoxBG.TabIndex = 0;
            this.pictureBoxBG.TabStop = false;
            this.pictureBoxBG.Click += new System.EventHandler(this.pictureBoxBG_Click);
            this.pictureBoxBG.MouseLeave += new System.EventHandler(this.pictureBoxBG_MouseLeave);
            this.pictureBoxBG.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBoxBG_MouseMove);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBoxNameOB);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.textBoxHeightOB);
            this.groupBox1.Controls.Add(this.textBoxWidthOB);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(5, 468);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(177, 129);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Detail : ";
            // 
            // textBoxNameOB
            // 
            this.textBoxNameOB.Location = new System.Drawing.Point(57, 104);
            this.textBoxNameOB.Name = "textBoxNameOB";
            this.textBoxNameOB.ReadOnly = true;
            this.textBoxNameOB.Size = new System.Drawing.Size(100, 20);
            this.textBoxNameOB.TabIndex = 5;
            this.textBoxNameOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 107);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Name :";
            // 
            // textBoxHeightOB
            // 
            this.textBoxHeightOB.Location = new System.Drawing.Point(57, 71);
            this.textBoxHeightOB.Name = "textBoxHeightOB";
            this.textBoxHeightOB.ReadOnly = true;
            this.textBoxHeightOB.Size = new System.Drawing.Size(47, 20);
            this.textBoxHeightOB.TabIndex = 3;
            this.textBoxHeightOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxWidthOB
            // 
            this.textBoxWidthOB.Location = new System.Drawing.Point(57, 36);
            this.textBoxWidthOB.Name = "textBoxWidthOB";
            this.textBoxWidthOB.ReadOnly = true;
            this.textBoxWidthOB.Size = new System.Drawing.Size(47, 20);
            this.textBoxWidthOB.TabIndex = 2;
            this.textBoxWidthOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 71);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Height : ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Width : ";
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel3.Controls.Add(this.listViewOB);
            this.panel3.Controls.Add(this.groupBox1);
            this.panel3.Location = new System.Drawing.Point(1012, 4);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(187, 602);
            this.panel3.TabIndex = 6;
            // 
            // listViewOB
            // 
            this.listViewOB.HideSelection = false;
            this.listViewOB.Location = new System.Drawing.Point(3, 3);
            this.listViewOB.Name = "listViewOB";
            this.listViewOB.Size = new System.Drawing.Size(177, 459);
            this.listViewOB.TabIndex = 1;
            this.listViewOB.UseCompatibleStateImageBehavior = false;
            this.listViewOB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewOB_MouseClick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.textBoxBGWidth);
            this.groupBox2.Controls.Add(this.textBoxBGHeigth);
            this.groupBox2.Location = new System.Drawing.Point(12, 580);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(339, 48);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Background Size: ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(194, 26);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Height : ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Width :";
            // 
            // textBoxBGWidth
            // 
            this.textBoxBGWidth.Location = new System.Drawing.Point(67, 23);
            this.textBoxBGWidth.Name = "textBoxBGWidth";
            this.textBoxBGWidth.ReadOnly = true;
            this.textBoxBGWidth.Size = new System.Drawing.Size(88, 20);
            this.textBoxBGWidth.TabIndex = 7;
            this.textBoxBGWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxBGHeigth
            // 
            this.textBoxBGHeigth.Location = new System.Drawing.Point(247, 23);
            this.textBoxBGHeigth.Name = "textBoxBGHeigth";
            this.textBoxBGHeigth.ReadOnly = true;
            this.textBoxBGHeigth.Size = new System.Drawing.Size(88, 20);
            this.textBoxBGHeigth.TabIndex = 8;
            this.textBoxBGHeigth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textBoxX);
            this.groupBox3.Controls.Add(this.textBoxY);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Location = new System.Drawing.Point(584, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(315, 48);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Position : ";
            // 
            // textBoxX
            // 
            this.textBoxX.Location = new System.Drawing.Point(58, 23);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.ReadOnly = true;
            this.textBoxX.Size = new System.Drawing.Size(88, 20);
            this.textBoxX.TabIndex = 3;
            this.textBoxX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxY
            // 
            this.textBoxY.Location = new System.Drawing.Point(220, 23);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.ReadOnly = true;
            this.textBoxY.Size = new System.Drawing.Size(88, 20);
            this.textBoxY.TabIndex = 2;
            this.textBoxY.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(188, 26);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(26, 13);
            this.label6.TabIndex = 1;
            this.label6.Text = "Y = ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(26, 26);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(26, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "X = ";
            // 
            // imageListOB
            // 
            this.imageListOB.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListOB.ImageStream")));
            this.imageListOB.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListOB.Images.SetKeyName(0, "Simon");
            this.imageListOB.Images.SetKeyName(1, "Torch");
            this.imageListOB.Images.SetKeyName(2, "Candle");
            this.imageListOB.Images.SetKeyName(3, "Gate");
            this.imageListOB.Images.SetKeyName(4, "BoundingMap");
            this.imageListOB.Images.SetKeyName(5, "Portal");
            this.imageListOB.Images.SetKeyName(6, "BottomStair");
            this.imageListOB.Images.SetKeyName(7, "TopStair");
            this.imageListOB.Images.SetKeyName(8, "Ground");
            this.imageListOB.Images.SetKeyName(9, "Whip");
            this.imageListOB.Images.SetKeyName(10, "Money");
            this.imageListOB.Images.SetKeyName(11, "Ball");
            this.imageListOB.Images.SetKeyName(12, "SmallHeart");
            this.imageListOB.Images.SetKeyName(13, "Heart");
            this.imageListOB.Images.SetKeyName(14, "Knife");
            this.imageListOB.Images.SetKeyName(15, "Axe");
            this.imageListOB.Images.SetKeyName(16, "Boomerang");
            this.imageListOB.Images.SetKeyName(17, "Crown");
            this.imageListOB.Images.SetKeyName(18, "Zombie");
            this.imageListOB.Images.SetKeyName(19, "BlackLeopard");
            this.imageListOB.Images.SetKeyName(20, "VampireBat");
            this.imageListOB.Images.SetKeyName(21, "FishMan");
            this.imageListOB.Images.SetKeyName(22, "BlackKnight");
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(310, 8);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 12;
            this.buttonSave.Text = "Save File";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // cancelPic
            // 
            this.cancelPic.Image = ((System.Drawing.Image)(resources.GetObject("cancelPic.Image")));
            this.cancelPic.Location = new System.Drawing.Point(930, 3);
            this.cancelPic.Name = "cancelPic";
            this.cancelPic.Size = new System.Drawing.Size(29, 31);
            this.cancelPic.TabIndex = 14;
            this.cancelPic.TabStop = false;
            this.cancelPic.Click += new System.EventHandler(this.cancelPic_Click);
            // 
            // removePic
            // 
            this.removePic.Image = ((System.Drawing.Image)(resources.GetObject("removePic.Image")));
            this.removePic.Location = new System.Drawing.Point(965, 4);
            this.removePic.Name = "removePic";
            this.removePic.Size = new System.Drawing.Size(32, 33);
            this.removePic.TabIndex = 15;
            this.removePic.TabStop = false;
            this.removePic.Click += new System.EventHandler(this.removePic_Click);
            // 
            // buttonSaveImg
            // 
            this.buttonSaveImg.Location = new System.Drawing.Point(222, 8);
            this.buttonSaveImg.Name = "buttonSaveImg";
            this.buttonSaveImg.Size = new System.Drawing.Size(75, 23);
            this.buttonSaveImg.TabIndex = 16;
            this.buttonSaveImg.Text = "Save Image";
            this.buttonSaveImg.UseVisualStyleBackColor = true;
            this.buttonSaveImg.Click += new System.EventHandler(this.buttonSaveImg_Click);
            // 
            // saveImgFileDialog
            // 
            this.saveImgFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveImgFileDialog_FileOk);
            // 
            // btnLoadObject
            // 
            this.btnLoadObject.Location = new System.Drawing.Point(131, 8);
            this.btnLoadObject.Margin = new System.Windows.Forms.Padding(2);
            this.btnLoadObject.Name = "btnLoadObject";
            this.btnLoadObject.Size = new System.Drawing.Size(86, 22);
            this.btnLoadObject.TabIndex = 17;
            this.btnLoadObject.Text = "Load object";
            this.btnLoadObject.UseVisualStyleBackColor = true;
            this.btnLoadObject.Click += new System.EventHandler(this.btnLoadObject_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnChangeCellSize);
            this.groupBox4.Controls.Add(this.tbCellSize);
            this.groupBox4.Location = new System.Drawing.Point(390, 8);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox4.Size = new System.Drawing.Size(175, 43);
            this.groupBox4.TabIndex = 18;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Cell Size";
            // 
            // btnChangeCellSize
            // 
            this.btnChangeCellSize.Location = new System.Drawing.Point(106, 16);
            this.btnChangeCellSize.Margin = new System.Windows.Forms.Padding(2);
            this.btnChangeCellSize.Name = "btnChangeCellSize";
            this.btnChangeCellSize.Size = new System.Drawing.Size(56, 22);
            this.btnChangeCellSize.TabIndex = 5;
            this.btnChangeCellSize.Text = "change";
            this.btnChangeCellSize.UseVisualStyleBackColor = true;
            this.btnChangeCellSize.Click += new System.EventHandler(this.btnChangeCellSize_Click);
            // 
            // tbCellSize
            // 
            this.tbCellSize.Location = new System.Drawing.Point(5, 18);
            this.tbCellSize.Name = "tbCellSize";
            this.tbCellSize.Size = new System.Drawing.Size(88, 20);
            this.tbCellSize.TabIndex = 4;
            this.tbCellSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.numY);
            this.groupBox5.Controls.Add(this.numX);
            this.groupBox5.Controls.Add(this.numHeight);
            this.groupBox5.Controls.Add(this.numWidth);
            this.groupBox5.Controls.Add(this.tbObjId);
            this.groupBox5.Controls.Add(this.label14);
            this.groupBox5.Controls.Add(this.numObjDelay);
            this.groupBox5.Controls.Add(this.label13);
            this.groupBox5.Controls.Add(this.label11);
            this.groupBox5.Controls.Add(this.label12);
            this.groupBox5.Controls.Add(this.tbObjName);
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Controls.Add(this.label8);
            this.groupBox5.Location = new System.Drawing.Point(364, 580);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox5.Size = new System.Drawing.Size(633, 48);
            this.groupBox5.TabIndex = 19;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "ObjectInfo";
            // 
            // numY
            // 
            this.numY.Location = new System.Drawing.Point(494, 20);
            this.numY.Margin = new System.Windows.Forms.Padding(2);
            this.numY.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numY.Name = "numY";
            this.numY.Size = new System.Drawing.Size(46, 20);
            this.numY.TabIndex = 21;
            this.numY.ValueChanged += new System.EventHandler(this.numY_ValueChanged);
            // 
            // numX
            // 
            this.numX.Location = new System.Drawing.Point(423, 20);
            this.numX.Margin = new System.Windows.Forms.Padding(2);
            this.numX.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numX.Name = "numX";
            this.numX.Size = new System.Drawing.Size(48, 20);
            this.numX.TabIndex = 20;
            this.numX.ValueChanged += new System.EventHandler(this.numX_ValueChanged);
            // 
            // numHeight
            // 
            this.numHeight.Location = new System.Drawing.Point(352, 20);
            this.numHeight.Margin = new System.Windows.Forms.Padding(2);
            this.numHeight.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.numHeight.Name = "numHeight";
            this.numHeight.Size = new System.Drawing.Size(46, 20);
            this.numHeight.TabIndex = 19;
            this.numHeight.ValueChanged += new System.EventHandler(this.numHeight_ValueChanged);
            // 
            // numWidth
            // 
            this.numWidth.Location = new System.Drawing.Point(255, 21);
            this.numWidth.Margin = new System.Windows.Forms.Padding(2);
            this.numWidth.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.numWidth.Name = "numWidth";
            this.numWidth.Size = new System.Drawing.Size(48, 20);
            this.numWidth.TabIndex = 18;
            this.numWidth.ValueChanged += new System.EventHandler(this.numWidth_ValueChanged);
            // 
            // tbObjId
            // 
            this.tbObjId.Location = new System.Drawing.Point(31, 21);
            this.tbObjId.Name = "tbObjId";
            this.tbObjId.ReadOnly = true;
            this.tbObjId.Size = new System.Drawing.Size(42, 20);
            this.tbObjId.TabIndex = 17;
            this.tbObjId.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 23);
            this.label14.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(22, 13);
            this.label14.TabIndex = 16;
            this.label14.Text = "Id :";
            // 
            // numObjDelay
            // 
            this.numObjDelay.Location = new System.Drawing.Point(588, 19);
            this.numObjDelay.Margin = new System.Windows.Forms.Padding(2);
            this.numObjDelay.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numObjDelay.Name = "numObjDelay";
            this.numObjDelay.Size = new System.Drawing.Size(41, 20);
            this.numObjDelay.TabIndex = 15;
            this.numObjDelay.ValueChanged += new System.EventHandler(this.numObjDelay_ValueChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(544, 23);
            this.label13.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(47, 13);
            this.label13.TabIndex = 13;
            this.label13.Text = "SceneId";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(476, 24);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(26, 13);
            this.label11.TabIndex = 10;
            this.label11.Text = "Y = ";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(403, 22);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(26, 13);
            this.label12.TabIndex = 9;
            this.label12.Text = "X = ";
            // 
            // tbObjName
            // 
            this.tbObjName.Location = new System.Drawing.Point(122, 20);
            this.tbObjName.Name = "tbObjName";
            this.tbObjName.ReadOnly = true;
            this.tbObjName.Size = new System.Drawing.Size(89, 20);
            this.tbObjName.TabIndex = 8;
            this.tbObjName.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(76, 23);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 13);
            this.label10.TabIndex = 7;
            this.label10.Text = "Name :";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(308, 24);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 13);
            this.label9.TabIndex = 5;
            this.label9.Text = "Height : ";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(215, 23);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 13);
            this.label8.TabIndex = 3;
            this.label8.Text = "Width : ";
            // 
            // MapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(1201, 637);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.btnLoadObject);
            this.Controls.Add(this.buttonSaveImg);
            this.Controls.Add(this.removePic);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.cancelPic);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.buttonLoad);
            this.Name = "MapEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Map Editor";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBG)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cancelPic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.removePic)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numObjDelay)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBoxBG;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxWidthOB;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxBGWidth;
        private System.Windows.Forms.TextBox textBoxBGHeigth;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ImageList imageListOB;
        private System.Windows.Forms.TextBox textBoxNameOB;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ListView listViewOB;
        private System.Windows.Forms.PictureBox cancelPic;
        private System.Windows.Forms.PictureBox removePic;
        private System.Windows.Forms.Button buttonSaveImg;
        private System.Windows.Forms.SaveFileDialog saveImgFileDialog;
        private System.Windows.Forms.Button btnLoadObject;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnChangeCellSize;
        private System.Windows.Forms.TextBox tbCellSize;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox textBoxHeightOB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numObjDelay;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tbObjName;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox tbObjId;
        private System.Windows.Forms.NumericUpDown numHeight;
        private System.Windows.Forms.NumericUpDown numWidth;
        private System.Windows.Forms.NumericUpDown numY;
        private System.Windows.Forms.NumericUpDown numX;
    }
}

