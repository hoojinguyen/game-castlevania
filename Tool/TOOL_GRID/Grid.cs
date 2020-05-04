using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    struct Cell
    {
        public List<int> listIdObj;
    };

    class Grid
    {
        public int gridWidth { get; set; }
        public int gridHeight { get; set; }
        public int cellSize { get; set; }
        public Cell[,] listCells { get; set; }
        public int numXCells { get; set; }
        public int numYCells { get; set; }

        public int NumXCells
        {
            get { return numXCells; }
            set { numXCells = value; }
        }

        public int NumYCells
        {
            get { return numYCells; }
            set { numYCells = value; }
        }

        public void CreateGrid(int width, int height, int cellSize)
        {
            this.gridWidth = width;
            this.gridHeight = height;
            this.cellSize = cellSize;

            double numX = Convert.ToDouble(this.gridWidth) / this.cellSize;
            double numY = Convert.ToDouble(this.gridHeight) / this.cellSize;
            this.numXCells = Convert.ToInt32(Math.Ceiling(numX));
            this.numYCells = Convert.ToInt32(Math.Ceiling(numY));

            //Allocate all the Cells
            listCells = new Cell[numXCells, numYCells];

            for (int i = 0; i < numXCells; i++)
            {
                for (int j = 0; j < numYCells; j++)
                {
                    listCells[i, j] = new Cell
                    {
                        listIdObj = new List<int>()
                    };
                }

            }
        }

        private bool checkExistCell(int cellX, int cellY)
        {
            if (cellX < 0 || cellX >= numXCells) return false;
            if (cellY < 0 || cellY >= numYCells) return false;
            return true;
        }

        public void clearObject()
        {
            for (int i = 0; i < numXCells; i++)
            {
                for (int j = 0; j < numYCells; j++)
                {
                    listCells[i, j].listIdObj.Clear();

                }
            }
        }

        public void AddObjToCell(Object obj, int index)
        {
            //remove player to grid
            if (obj.Id == 1)
            {
                return;
            }

            float left, top, right, bottom;

            left = obj.PosX;
            top = obj.PosY;
            right = left + obj.Width;
            bottom = top + obj.Height;

            int cellLeft = (int)(left / cellSize);
            int cellRight = (int)(right / cellSize);
            int cellTop = (int)(top / cellSize);
            int cellBottom = (int)(bottom / cellSize);

            if (cellLeft == cellRight)
            {
                if (cellTop == cellBottom)
                {
                    if (checkExistCell(cellLeft, cellTop))
                        listCells[cellLeft, cellTop].listIdObj.Add(index);
                }
                else
                {
                    for (int j = cellTop; j <= cellBottom; j++)
                    {
                        if (checkExistCell(cellLeft, j))
                            listCells[cellLeft, j].listIdObj.Add(index);
                    }
                }
            }
            else
            {
                if (cellTop == cellBottom)
                {
                    for (int j = cellLeft; j <= cellRight; j++)
                    {
                        if (checkExistCell(j, cellTop))
                            listCells[j, cellTop].listIdObj.Add(index);
                    }
                }
                else
                {
                    for (int j = cellLeft; j <= cellRight; j++)
                    {
                        for (int k = cellTop; k <= cellBottom; k++)
                        {
                            if (checkExistCell(j, k))
                                listCells[j, k].listIdObj.Add(index);
                        }
                    }
                }
            }
        }
    }
}
