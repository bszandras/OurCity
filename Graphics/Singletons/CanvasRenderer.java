package Graphics.Singletons;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.*;
import java.util.ArrayList;

import Graphics.Sprite;
import Graphics.Vector2;

public class CanvasRenderer extends Canvas {

    private static CanvasRenderer instance = null;
    private ArrayList<Sprite> sortedSprites = new ArrayList<>();
    public CanvasRenderer()
    {
        instance = this;
    }
    public static void SortRenderables()
    {
        if(instance == null)
        {
            System.out.println("Renderer instance is null");
            return;
        }
        
        instance.sortedSprites.clear();
        for (Sprite sprite : OrthoWorld.GetSprites()) {
            if(instance.sortedSprites.isEmpty())
            {
                instance.sortedSprites.add(sprite);
            }
            else
            {
                for (int i = 0; i < instance.sortedSprites.size(); i++) {
                    if(sprite.getSortingWeight().getY() < instance.sortedSprites.get(i).getSortingWeight().getY())
                    {

                        instance.sortedSprites.add(i, sprite);
                        break;
                    }
                    else if(i == instance.sortedSprites.size()-1)
                    {
                        instance.sortedSprites.add(sprite);
                        break;
                    }
                }
            }
        }
    }

    public static void Draw(Graphics2D graphics2d)
    {
        if(OrthoWorld.Exists())
        {
            int renderedSprites = 0;
            if(OrthoWorld.Exists())
            {
                for (Sprite sprite : instance.sortedSprites) {
                    renderedSprites += sprite.draw(graphics2d, new Vector2(instance.getWidth(), instance.getHeight()));
                }
                //g2.drawImage(buffy, null, 0, 0);
                graphics2d.setColor(Color.BLUE);
                //graphics2d.fillRect(instance.getWidth()/2-renderedSprites/2, instance.getHeight()/2-renderedSprites/2, renderedSprites, renderedSprites);
            }
            //System.out.println("Rendered sprites: " + renderedSprites);
        }
    }
}
