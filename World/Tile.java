package World;
import Graphics.Sprite;
import Graphics.Singletons.OrthoWorld;

public class Tile {
    private Entity owEntity = null;
    private Sprite groundSprite = null;
    private int x;
    private int y;
    public Tile(int x, int y)
    {
        this.x = x;
        this.y = y;
        groundSprite = new Sprite((x * 64) - y * 32, (y * 64) - y * 40, "Graphics/OrthoSprites/ortho-ground.png");
        OrthoWorld.AddSprite(groundSprite);
    }
    public void SetEntity(Entity e)
    {
        owEntity = e;
    }
}
