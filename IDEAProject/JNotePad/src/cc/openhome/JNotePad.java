package cc.openhome;

import javax.swing.*;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;

public class JNotePad extends JFrame{
    private JMenuBar menuBar;
    private JMenu filemenu;
    private JMenuItem menuOpen;
    private JMenuItem menuSave;
    private JMenuItem menuSaveAs;
    private JMenuItem menuClose;

    private JMenu editMenu;
    private JMenuItem menuCut;
    private JMenuItem menuCopy;
    private JMenuItem menuPaste;

    private JMenu aboutMenu;
    private JMenuItem menuAbout;

    public JNotePad(){
        initComponents();
        initEventListeners();
    }

    private void initComponents(){
        setTitle("newTextDocumentary");
        setSize(400,300);
        initMenuBar();

    }
    private void initMenuBar(){
        menuBar=new JMenuBar();
        filemenu = new JMenu("file");
        menuOpen = new JMenuItem("Open");
        menuSave = new JMenuItem("Save");
        menuBar.add(filemenu);
        filemenu.add(menuOpen);
        filemenu.add(menuSave);
        menuOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, InputEvent.CTRL_MASK));
        setJMenuBar(menuBar);

    }

    private void initEventListeners(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static  void main(String[] agrs){
        javax.swing.SwingUtilities.invokeLater(()->{
            new JNotePad().setVisible(true);
        });
    }
}
