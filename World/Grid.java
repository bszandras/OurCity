package World;

public class Grid {
    Tile[][] grid;
    public Grid()
    {
        int size = 30;
        grid = new Tile[size][size];
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                grid[i][j] = new Tile(i, j);
                grid[i][j].SetEntity(new Entity(i, j));
            }
        }
    }
}
