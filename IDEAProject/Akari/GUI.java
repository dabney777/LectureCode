package com.dabney;
/**
 * Created by Dabney on 11/9/2016.
 */

import javafx.scene.control.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.*;

/**
 * Created by Dabney on 11/9/2016.
 */
public class GUI extends JFrame {
    private JButton [][]jbutton ;
    private JPanel panel;

    /*
     *  1.char 'l' mean block been lighted
     *  2.char 'w' mean *blank* block
     *  3.char 'b' mean black block
     *  4.char '2' mean a block with number '2'
     *  5.char '*' mean a marked block which thought can't be placed a bulb
     *  6.char 'x' mean a block with a bulb
     */

    public GUI(Frames f){
        super();
        Font buttonFont = new Font("华文行楷",Font.BOLD,25);
        this.setSize(f.columnMax*52, f.rowMax*55);
        jbutton = new JButton[f.rowMax][f.columnMax];

        for(int i =0;i<f.rowMax;i++){
            for(int j = 0 ; j<f.columnMax;j++){
                jbutton[i][j]= new JButton();

                jbutton[i][j].setSize(50,50);
                jbutton[i][j].setLocation(1+50*j,1+50*i);
                jbutton[i][j].setFont(buttonFont);
                jbutton[i][j].setForeground(Color.WHITE);


                switch (f.board[i][j]){
                    case 'l': jbutton[i][j].setBackground(Color.CYAN);break;
                    case 'w': jbutton[i][j].setBackground(Color.WHITE);break;
                    case 'b': jbutton[i][j].setBackground(Color.BLACK);break;
                    case '*': jbutton[i][j].setBackground(Color.LIGHT_GRAY);
                        jbutton[i][j].setText("*");
                        break;
                    case '0': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("0");
                        break;
                    case '1': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("1");
                        break;
                    case '2': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("2");
                        break;
                    case '3': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("3");
                        break;
                    case '4': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("4");
                        break;
                    case 'x': jbutton[i][j].setBackground(Color.YELLOW);break;
                    default:
                }
                this.add(jbutton[i][j]);
                jbutton[i][j].setVisible(true);
            }

        }
        this.add(new Panel());
    }
    public GUI(Frames f,char[][] _board){
        super();
        Font buttonFont = new Font("华文行楷",Font.BOLD,25);
        this.setSize(f.columnMax*52, f.rowMax*55);
        jbutton = new JButton[f.rowMax][f.columnMax];

        for(int i =0;i<f.rowMax;i++){
            for(int j = 0 ; j<f.columnMax;j++){
                jbutton[i][j]= new JButton();

                jbutton[i][j].setSize(50,50);
                jbutton[i][j].setLocation(1+50*j,1+50*i);
                jbutton[i][j].setFont(buttonFont);
                jbutton[i][j].setForeground(Color.WHITE);


                switch (_board[i][j]){
                    case 'l': jbutton[i][j].setBackground(Color.CYAN);break;
                    case 'w': jbutton[i][j].setBackground(Color.WHITE);break;
                    case 'b': jbutton[i][j].setBackground(Color.BLACK);break;
                    case '*': jbutton[i][j].setBackground(Color.LIGHT_GRAY);
                        jbutton[i][j].setText("*");
                        break;
                    case '0': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("0");
                        break;
                    case '1': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("1");
                        break;
                    case '2': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("2");
                        break;
                    case '3': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("3");
                        break;
                    case '4': jbutton[i][j].setBackground(Color.BLACK);
                        jbutton[i][j].setText("4");
                        break;
                    case 'x': jbutton[i][j].setBackground(Color.YELLOW);break;
                    default:
                }
                this.add(jbutton[i][j]);
                jbutton[i][j].setVisible(true);
            }

        }
        this.add(new Panel());
    }
}

