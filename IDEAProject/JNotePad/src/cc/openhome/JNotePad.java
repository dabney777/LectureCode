package cc.openhome;

import javax.swing.*;

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


    public JNotePad(){
        initComponents();
        initEventListeners();
    }

    private void initComponents(){
        setTitle("newTextDocumentary");
        setSize(400,300);
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
