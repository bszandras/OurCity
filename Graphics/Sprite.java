package Graphics;
import java.awt.Graphics2D;
import java.awt.Image;

import Graphics.Singletons.*;

public class Sprite {
    private Vector2 worldPosition;
    private float mainScaling = 1.0f;
    private Vector2 selfOriginOffset;
    private Vector2 dimensions;
    private Image image;
    private String imagePath;
    private Vector2 sortingWeight;

    //static data
    private static int spriteWidth = 128;
    private static int spriteHeight = 160;

    public Sprite(int x, int y, String path) {
        imagePath = path;
        image = TextureDictionary.GetTexture(path);
        selfOriginOffset = new Vector2(spriteWidth/2, spriteHeight - spriteWidth/2);

        //sprite origo correction
        //alapból a sprite-ot a megadott koordinátákra úgy rendereli az awt/swing,
        //hogy a sprite bal felső sarka kerül a megadott koordinátára
        //ezt úgy offsetelem, hogy a sprite alapja (zöld fű) a jövőbeli grid közepére kerül
        worldPosition = new Vector2(x, y);
        Vector2 newWorldPosition = new Vector2(x - selfOriginOffset.getX(), y - selfOriginOffset.getY());
        worldPosition.Add(newWorldPosition);
        
        //sprite méretei, jelenleg a kép felbontása szerint
        //ezt a grid mérete fogja kezelni
        //dimensions = new Vector2(image.getWidth(null), image.getHeight(null));
        dimensions = new Vector2(spriteWidth, image.getHeight(null));

        //a sprite sorting weightje 2 dologtól függ
        //1 a sprite y koordinátája
        //2 a sprite custom adattagja (x koordináta), ezt az alapján változtatjuk, hogy akarunk-e spec effecteket
        //pl azonos sorban az erdő sprite overlappolja a házakat (ilyen sprite egyelőre nincs)
        sortingWeight = new Vector2(0, y);
    }
    public int draw(Graphics2D g2, Vector2 windowSize) {
        //update texture
        if(Camera.getChangedZoomThisFram())
        {
            image = TextureDictionary.GetScaledTexture(imagePath);
        }

        mainScaling = Camera.getZoom();

        Vector2 zoomedPosition = OrthoWorld.WorldPositonToScreen(new Vector2((int)(worldPosition.getX() * mainScaling), 
                                                                                 (int)(worldPosition.getY() * mainScaling)));
        zoomedPosition = Camera.WorldPositionRelativeToCamera(zoomedPosition);
        Vector2 zoomedDimensions = new Vector2((int)(dimensions.getX() * mainScaling), 
                                               (int)(dimensions.getY() * mainScaling));
        
        //frustum culling
        if(zoomedPosition.getX() + zoomedDimensions.getX() < 0 || zoomedPosition.getX() > windowSize.getX() ||
           zoomedPosition.getY() + zoomedDimensions.getY() < 0 || zoomedPosition.getY() > windowSize.getY())
        {
            return 0;
        }

        if(image == null)
        {
            return 0;
        }

        //maga a rajzolás
        //mostmár ez nem scaleli a képet
        //kép scalelést a texture dictionary kezeli, amikor frissít a zoom
        g2.drawImage(image, zoomedPosition.getX(), zoomedPosition.getY(), null);
        return 1;
            
    }
    public void AddSortingWeightY(int y)
    {
        sortingWeight.Add(new Vector2(0, y));
    }
    public Vector2 getSortingWeight()
    {
        return sortingWeight;
    }
    public void SetImage(Image image)
    {
        this.image = image;
    }
    public void SetPosition(Vector2 position)
    {
        worldPosition = position;
        Vector2 newWorldPosition = new Vector2(position.getX() - selfOriginOffset.getX(), position.getY() - selfOriginOffset.getY());
        worldPosition.Add(newWorldPosition);
    }
}
