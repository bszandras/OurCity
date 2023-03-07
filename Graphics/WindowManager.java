package Graphics;

import java.awt.*;
import java.awt.event.*;
import java.awt.event.KeyListener;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

import javax.swing.Timer;
import javax.swing.event.MouseInputListener;
import javax.swing.JFrame;

import Graphics.Singletons.*;
import World.*;

public class WindowManager {

    private JFrame frame;
    //private Renderer renderer;
    //private World world;
    private Boolean paused = true;

    //fps
    private int targetTicksPerSecond = 1000;
    private final Timer tickTimer;
    private long frameTime = 0;

    //input
    private ArrayList<Integer> currentlyPressedKeys = new ArrayList<Integer>();
    private int mouseDirection = 0;
    private int rightClick = 0;
    private Vector2 lastMousePosition = new Vector2();
    private Vector2 currentMousePosition = new Vector2();

    private Vector2 mousePosAtClick = new Vector2();
    private Sprite mouseTestSprite;

    //new render
    BufferStrategy bufferStrategy;
    BufferedImage bufferedImage;

    public WindowManager() {
        
        //window init
        frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.addKeyListener(new CustomKeyListener());
        frame.addMouseWheelListener(new CustomMouseWheelListener());
        frame.addMouseListener(new CustomMouseListener());
        frame.addMouseMotionListener(new CustomMouseListener());
        frame.setVisible(true);
        
        Vector2 windowSize = new Vector2(750,750);

        //texture dictionary
        new TextureDictionary();
        //camera init
        Camera camera = new Camera(new Vector2(0,0));
        //renderer
        CanvasRenderer r = new CanvasRenderer();
        //ortho
        OrthoWorld ortho = new OrthoWorld(new Vector2(700,700), windowSize);
        Grid grid = new Grid();

        //game loop
        tickTimer = new Timer(0, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                if(paused)
                {
                    return;
                }
                Update();
                Render();
            }
        });
        tickTimer.start();

        //meg kell hívni sprite új sprite-nál, sprite törlésnél, sprite cserénél
        //freme-enként hívni költséges lehet
        CanvasRenderer.SortRenderables();
        
        //window befejezés
        frame.setBounds(0, 0, windowSize.getX(), windowSize.getY());
        frame.setIgnoreRepaint(true);
        frame.add(r);

        //render előkészítés
        r.setIgnoreRepaint(true);
        r.createBufferStrategy(2);
        bufferStrategy = r.getBufferStrategy();

        bufferedImage = GraphicsEnvironment.getLocalGraphicsEnvironment()
            .getDefaultScreenDevice()
            .getDefaultConfiguration()
            .createCompatibleImage(windowSize.getX(), windowSize.getY());
        paused = false;
    }

    private void Update()
    {
        //System.out.println("frame start: " + (System.nanoTime() - frameTime) / 1000000);
        //frameTime = System.nanoTime();
        //game logic
        //camera move logic - key event processing
        //minden ami gombnyomásra történik annak ide kell kerülnie
        for(Integer key : currentlyPressedKeys) {
            //camera movement
            Vector2 dir = new Vector2();
            float zoom = 0;
            switch(key) {
                case KeyEvent.VK_W:
                    dir.Add(new Vector2(0, -1));
                    break;
                case KeyEvent.VK_A:
                    dir.Add(new Vector2(-1, 0));
                    break;
                case KeyEvent.VK_S:
                    dir.Add(new Vector2(0, 1));
                    break;
                case KeyEvent.VK_D:
                    dir.Add(new Vector2(1, 0));
                    break;
                case KeyEvent.VK_K:
                    zoom += -0.1f;
                    break;
                case KeyEvent.VK_L:
                    zoom += 0.1f;
                    break;
            }
            Camera.Move(dir);
            Camera.Zoom(zoom);
        }
        //camera zoom logic
        if(mouseDirection != 0)
        {
            Camera.Zoom(mouseDirection * 0.1f);
            mouseDirection = 0;
        }

        //camera drag
        if(rightClick == 1)
        {
            currentMousePosition = MousePositionInWorldSpace();
            System.out.println(MousePositionInWorldSpace());
            lastMousePosition = currentMousePosition;
            /*
                currentMousePosition = MousePositionInWorldSpace();
                Vector2 dir = Vector2.Sub(lastMousePosition, currentMousePosition);
                //dir.Scale(-1);
                dir.Scale(0.5f);
                Camera.Move(dir);
                lastMousePosition = currentMousePosition;
                */
                //frame.getMousePosition().setLocation(currentMousePosition.getX(), currentMousePosition.getY());
        }
        else
        {
            lastMousePosition = MousePositionInWorldSpace();
        }
    }
    private void Render()
    {
        //render logic
        Graphics2D g2d = bufferedImage.createGraphics();
        try
        {
            //background
            g2d.setColor(Color.blue);
            g2d.fillRect(0, 0, 750, 750);

            //rendering
            CanvasRenderer.Draw(g2d);
            
            Graphics graphics = bufferStrategy.getDrawGraphics();
            try
            {
                graphics.drawImage(bufferedImage, 0, 0, null);
                if (!bufferStrategy.contentsLost())
                {
                    bufferStrategy.show();
                }
            }
            finally
            {
                graphics.dispose();
            }
        }
        finally
        {
            g2d.dispose();
        }
        Thread.yield();

        //frame.repaint();
        //System.out.println("frame end: " + (System.nanoTime() - frameTime) / 1000000);
        frameTime = System.nanoTime();
    }
    class CustomKeyListener implements KeyListener
    {
        public CustomKeyListener()
        {
            
        }
        public void keyTyped(KeyEvent e)
        {
        }
        public void keyPressed(KeyEvent e)
        {
            if(paused || currentlyPressedKeys.contains(e.getKeyCode()))
            {
                return;
            }
            currentlyPressedKeys.add(e.getKeyCode());
        }
        public void keyReleased(KeyEvent e)
        {
            if(currentlyPressedKeys.contains(e.getKeyCode()))
            {
                currentlyPressedKeys.remove((Integer)e.getKeyCode());
            }
   
        }   
    }
    class CustomMouseWheelListener implements MouseWheelListener
    {
        public CustomMouseWheelListener() {
        }
        public void mouseWheelMoved(MouseWheelEvent e) {
            if(paused)
            {
                return;
            }
            if (e.getScrollType() == MouseWheelEvent.WHEEL_UNIT_SCROLL) {
                if(e.getWheelRotation() < 0)
                {
                    //up
                    mouseDirection = 1;
                }
                else
                {
                    //down
                    mouseDirection = -1;
                }
            }
        }
    }
    class CustomMouseListener implements MouseInputListener
    {
        public CustomMouseListener() {
        }
        public void mouseClicked(MouseEvent e)
        {    
        }
        public void mousePressed(MouseEvent e)
        {
            if(paused)
            {
                return;
            }
            if(e.getButton() == MouseEvent.BUTTON1)
            {
                //left click
            }
            else if(e.getButton() == MouseEvent.BUTTON3)
            {
                //right click
                rightClick = 1;
                mousePosAtClick = new Vector2((int)frame.getMousePosition().getX(), (int)frame.getMousePosition().getY());

                /*
                Vector2 pos = new Vector2(e.getX(), e.getY());
                //ezzel kivonjuk a játékablak tetején a windows gombjait
                if(!frame.isUndecorated())
                {
                    pos.Sub(new Vector2(0,30));
                }
                pos = Camera.ScreenPositionToScaledWorldPosition(pos);
                //System.out.println(pos);
                lastMousePosition = pos;
                */
            }
        }
        public void mouseReleased(MouseEvent e) {
            if(paused)
            {
                return;
            }
            if(e.getButton() == MouseEvent.BUTTON1)
            {
                //left click
            }
            else if(e.getButton() == MouseEvent.BUTTON3)
            {
                //right click
                rightClick = 0;
                /*
                GraphicsEnvironment ge = 
                        GraphicsEnvironment.getLocalGraphicsEnvironment();
                GraphicsDevice[] gs = ge.getScreenDevices();

                Robot r = null;
                try {
                    r = new Robot(gs[0]);
                } catch (AWTException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                if(r != null)
                {
                    r.mouseMove((int)mousePosAtClick.getX(), (int)mousePosAtClick.getY());
                }
                */
                //frame.getMousePosition().setLocation(mousePosAtClick.getX(), mousePosAtClick.getY());
                //frame.getMousePosition().setLocation(mousePosAtClick.getX(), mousePosAtClick.getY());
            }
        }
        public void mouseEntered(MouseEvent e) 
        {
        }
        public void mouseExited(MouseEvent e)
        {
        }
        public void mouseDragged(MouseEvent e)
        {
        }
        public void mouseMoved(MouseEvent e)
        {
        }
    }
    private Vector2 MousePositionInWorldSpace()
    {
        Point mouse = frame.getMousePosition();
        if(mouse == null)
        {
            return new Vector2(0,0);
        }
        Vector2 pos = new Vector2((int)(mouse.getX()), (int)(mouse.getY()));
        //ezzel kivonjuk a játékablak tetején a windows gombjait
        if(!frame.isUndecorated())
        {
            pos.Sub(new Vector2(0,30));
        }
        pos = Camera.ScreenPositionToScaledWorldPosition(pos);
        return pos;
    }
}