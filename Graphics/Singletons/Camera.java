package Graphics.Singletons;

import Graphics.Vector2;

public class Camera {
    private static Camera instance = null;
    private Vector2 position;
    private float zoom = 1.4f;
    private Boolean changedZoomThisFram = false;
    private float furthestZoom = 1.1f;
    private float closestZoom = 1.9f;
    private int cameraSpeed = 3;
    public Camera(Vector2 pos)
    {
        instance = this;
        position = pos;
    }

    public static int getPosX() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return 0;
        }
        return instance.position.getX();
    }
    public static int getPosY() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return 0;
        }
        return instance.position.getY();
    }
    public static Vector2 getPosition() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return new Vector2(0,0);
        }
        return instance.position;
    }
    public static void Move(Vector2 direction)
    {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return;
        }

        direction.Scale(instance.cameraSpeed);
        instance.position.Add(direction);
    }
    public static void Zoom(float amount)
    {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return ;
        }

        instance.zoom += amount * instance.zoom;
        if(instance.zoom < instance.furthestZoom)
        {
            instance.zoom = instance.furthestZoom;
        }
        else if(instance.zoom > instance.closestZoom)
        {
            instance.zoom = instance.closestZoom;
        }

        if(amount != 0)
        {
            instance.changedZoomThisFram = true;
            TextureDictionary.ScaleTextures(instance.zoom);
        }
        else
        {
            instance.changedZoomThisFram = false;
        }
        
    }
    public static float getZoom() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return 0;
        }

        return instance.zoom;
    }
    public static Boolean getChangedZoomThisFram() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return false;
        }

        return instance.changedZoomThisFram;
    }
    public static String InstanceToString() {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return "Camera instance is null";
        }

        return "Camera [position=" + instance.position + "]";
    }

    public static Vector2 WorldPositionRelativeToCamera(Vector2 pos)
    {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return new Vector2(0,0);
        }
        return new Vector2(pos.getX() - (int)(getPosX() * getZoom()), pos.getY() - (int)(getPosY() * getZoom()));
    }
    public static Vector2 ScreenPositionToScaledWorldPosition(Vector2 pos)
    {
        if(instance == null)
        {
            System.out.println("Camera instance is null");
            return new Vector2(0,0);
        }
        //reverse conversion from screen to world space
        pos = Vector2.Add(pos, new Vector2((int)(getPosX() * getZoom()), (int)(getPosY() * getZoom())));
        pos = Vector2.Sub(pos, OrthoWorld.getOrigoOffset());
        pos.Scale(1 / getZoom());
        //ez azért kell, mert az egész világ felezve van,
        //hogy a sprite-ok normális zoom esetén a felbontásuk felét használják csak
        //így bezoomolva lesznek extra pixelek a textúrákon, amik normál zoomon nem látszanak
        pos.Scale(0.5f);
        return pos;
    }
}
