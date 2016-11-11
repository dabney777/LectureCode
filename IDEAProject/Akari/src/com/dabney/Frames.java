/*
 *  1.char 'l' mean block been lighted
 *  2.char 'w' mean *blank* block
 *  3.char 'b' mean black block
 *  4.char '2' mean a block with number '2'
 *  5.char '*' mean a marked block which thought can't be placed a bulb and not be lighted
 *  6.char 'x' mean a block with a bulb
 *  7.char '#' mean a block shouldn't be placed a bulb and be lighted
 *  8.char '5' mean a block be lighted by 1 bulb
 */

package com.dabney;


//import javax.swing.*;
//import javax.xml.crypto.Data;
import com.sun.xml.internal.ws.api.message.ExceptionHasMessage;

import javax.xml.datatype.DatatypeConfigurationException;
//import java.awt.event.*;
//import java.awt.*;
import java.io.*;
import java.util.Vector;


public class Frames {
    static int rowMax =0, columnMax =0;
    static int count =0;
    char [][] board;
    private static int changeCount =0,oldChangeCount=0;
    public Frames(int _row, int _column)
                        throws DatatypeConfigurationException
    {
        board = new char[_row][_column];
        rowMax = _row;
        columnMax = _column;
        if(deployed()==false) throw new DatatypeConfigurationException("wrong input");

        GUI monitor = new GUI(this,board);
        monitor.setTitle("题目");
        monitor.setVisible(true);
    }
    private void changeTo(char[][] _board,int i , int j,char goal){ //i is rowMax serial , j is columnMax serial
        if(i<0||j<0||i>= rowMax ||j>= columnMax) return;
        switch (_board[i][j]){
            case 'b':return;
            case 'l':return;
            case 'w':if(goal==_board[i][j]){changeCount++;}else
            {_board[i][j] = goal;}break;
            case '*':if(goal==_board[i][j]||goal=='x'){changeCount++;}else
            {_board[i][j] = goal;}break;

            default:
                    return;

        }
        if (_board[i][j]=='x') lightRowAndColumn(_board,i,j);
        return;
    }
    private void lightRowAndColumn(char [][] _board,int i,int j){
        Out1:for(int columnNum = j+1; columnNum< columnMax; columnNum++){
            switch (_board[i][columnNum]){
                case 'w':
                    _board[i][columnNum]='l';
                    break;
                case '*':
                    _board[i][columnNum]='l';
                    break;
                case 'l':break;
                default:
                    break Out1;

            }
        }
        Out2:for(int columnNum = j-1; columnNum>= 0; columnNum--) {
            switch (_board[i][columnNum]) {
                case 'w':
                    _board[i][columnNum] = 'l';
                    break;
                case '*':
                    _board[i][columnNum]='l';
                    break;
                case 'l':break;
                default:
                    break Out2;
            }
        }
        Out3:for(int rowNum = i-1; rowNum>= 0; rowNum--) {
            switch (_board[rowNum][j]) {
                case 'w':
                    _board[rowNum][j] = 'l';
                    break;
                case '*':
                    _board[rowNum][j]='l';
                    break;
                case 'l':break;
                default:
                    break Out3;
            }
        }
        Out4:for(int rowNum = i+1; rowNum<rowMax; rowNum++) {
            switch (_board[rowNum][j]) {
                case 'w':
                    _board[rowNum][j] = 'l';
                    break;
                case '*':
                    _board[rowNum][j]='l';
                    break;
                case 'l':break;
                default:
                    break Out4;
            }
        }
    }
    private boolean check(char[][] _board){
        for(char [] i:_board) {
            for (char j : i) {
              if(j=='w'||j=='*')
                  return false;
            }
        }
        return true;
    }
    private int getEmptyPositionQuantity(int i, int j){
        int Quantity =0;

        if(j+1< columnMax && board[i][j+1]=='w') Quantity++;
        if(j-1>=0         && board[i][j-1]=='w') Quantity++;
        if(i+1< rowMax    && board[i+1][j]=='w') Quantity++;
        if(i-1>=0         && board[i-1][j]=='w') Quantity++;
        if(j+1< columnMax && board[i][j+1]=='x') Quantity--;
        if(j-1>=0         && board[i][j-1]=='x') Quantity--;
        if(i+1< rowMax    && board[i+1][j]=='x') Quantity--;
        if(i-1>=0         && board[i-1][j]=='x') Quantity--;

        return Quantity;

    }
    private void Step1(){oldChangeCount = changeCount;
        do {  for (int i = 0; i < rowMax; i++) {
            for (int j = 0; j < columnMax; j++) {
                switch (board[i][j]) {
                    case '4':
                        changeTo(board,i - 1, j, 'x');
                        changeTo(board,i + 1, j, 'x');
                        changeTo(board,i, j - 1, 'x');
                        changeTo(board,i, j + 1, 'x');
                        break;
                    case '3':
                        if (getEmptyPositionQuantity(i, j) == 3) {
                            changeTo(board,i - 1, j, 'x');
                            changeTo(board,i + 1, j, 'x');
                            changeTo(board,i, j - 1, 'x');
                            changeTo(board,i, j + 1, 'x');
                        }
                        break;
                    case '2':
                        if (getEmptyPositionQuantity(i, j) == 2) {
                            changeTo(board,i - 1, j, 'x');
                            changeTo(board,i + 1, j, 'x');
                            changeTo(board,i, j - 1, 'x');
                            changeTo(board,i, j + 1, 'x');
                        }
                        break;
                    case '1':
                        if (getEmptyPositionQuantity(i, j) == 1) {
                            changeTo(board,i - 1, j, 'x');
                            changeTo(board,i + 1, j, 'x');
                            changeTo(board,i, j - 1, 'x');
                            changeTo(board,i, j + 1, 'x');
                        }
                        break;
                    case '0':
                        if(j+1< columnMax  && board[i][j+1]=='w') board[i][j+1]='*';
                        if(j-1>=0          && board[i][j-1]=='w') board[i][j-1]='*';
                        if(i+1< rowMax     && board[i+1][j]=='w') board[i+1][j]='*';
                        if(i-1>=0          && board[i-1][j]=='w') board[i-1][j]='*';
                        break;
                    default:

                }

            }

        }
        }while(changeCount!=oldChangeCount);
    }
    private int bulbQuantity(int i,int j,char [][]_board){
        int Quantity=0;
        if(j+1< columnMax  && _board[i][j+1]=='x') Quantity++;
        if(j-1>=0          && _board[i][j-1]=='x') Quantity++;
        if(i+1< rowMax     && _board[i+1][j]=='x') Quantity++;
        if(i-1>=0          && _board[i-1][j]=='x') Quantity++;
        return Quantity;
    }
    private int[] findWhiteBlock(char[][] _board,int i,int j){
        int []a;
        if(j+1< columnMax  && _board[i][j+1]=='w') return a=new int[]{i,j+1};
        if(j-1>=0          && _board[i][j-1]=='w') return a=new int[]{i,j-1};
        if(i+1< rowMax     && _board[i+1][j]=='w') return a=new int[]{i+1,j};
        if(i-1>=0          && _board[i-1][j]=='w') return a=new int[]{i-1,j};
        return a=new int[]{-1,-1};

    }

    private boolean deadpoint(char [][]_board){
        for(int i = 0;i < rowMax;i++){
            for(int j =0 ; j<columnMax;j++){
                if(_board[i][j]=='w'){
                    return false;
                }
            }}
        return true;
    }

    private void solveDigital(char [][] _board)throws Exception
    {


        for(int i = 0;i < rowMax;i++){
            for(int j =0 ; j<columnMax;j++){
                char [][]newBoard1 = new char[rowMax][columnMax];
                for(int m =0;m<rowMax;m++){
                    newBoard1[m]=_board[m].clone();
                }
                char [][]newBoard2 = new char[rowMax][columnMax];
                for(int m =0;m<rowMax;m++){
                    newBoard2[m]=_board[m].clone();
                }

                switch (_board[i][j]){


                    case '3':if(bulbQuantity(i,j,_board)>=3) {break;}else {
                            int []white=findWhiteBlock(newBoard1,i,j);
                            if(white[0]==-1) throw new Exception(" wrong frames"+i+"\t"+j);
                            changeTo(newBoard1, white[0], white[1], 'x');
                            solveDigital(newBoard1);
                            changeTo(newBoard2,white[0],white[1],'*');
                            solveDigital(newBoard2);
                        break;
                    }
                    case '2':if(bulbQuantity(i,j,_board)>=2) {break;}else {

                            int []white=findWhiteBlock(newBoard1,i,j);
                            if(white[0]==-1) throw new Exception(" wrong frames"+i+"\t"+j);
                            changeTo(newBoard1,white[0],white[1],'x');
                            solveDigital(newBoard1);
                            changeTo(newBoard2,white[0],white[1],'*');
                            solveDigital(newBoard2);
                        break;
                    }
                    case '1':if(bulbQuantity(i,j,_board)>=1) {
                        break;}else {
                            int []white=findWhiteBlock(_board, i,j);
                            if(white[0]==-1) return ;
                        changeTo(newBoard2,white[0],white[1],'*');
                        solveDigital(newBoard2);
                            changeTo(newBoard1,white[0],white[1],'x');
                            solveDigital(newBoard1);


                    }break;

                    default:

                }

            }
        }
        for(int i = 0;i < rowMax;i++){
            for(int j =0 ; j<columnMax;j++){
                switch (_board[i][j]){
                    case '3':if(bulbQuantity(i,j,_board)>=3) {
                        changeTo(_board,i - 1, j, '*');
                        changeTo(_board,i + 1, j, '*');
                        changeTo(_board,i, j - 1, '*');
                        changeTo(_board,i, j + 1, '*');
                        break;
                    }else return;
                    case '2':if(bulbQuantity(i,j,_board)>=2) {
                        changeTo(_board,i - 1, j, '*');
                        changeTo(_board,i + 1, j, '*');
                        changeTo(_board,i, j - 1, '*');
                        changeTo(_board,i, j + 1, '*');
                        break;
                    }else return;

                    case '1':if(bulbQuantity(i,j,_board)>=1){
                        changeTo(_board,i - 1, j, '*');
                        changeTo(_board,i + 1, j, '*');
                        changeTo(_board,i, j - 1, '*');
                        changeTo(_board,i, j + 1, '*');
                        break;
                    }else return;

                    default:

                }

            }
        }
//        GUI monitor = new GUI(this,_board);
//        monitor.setName("main");
//        monitor.setVisible(true);

//        if(_board[8][6]=='x'&&_board[5][4]=='x'){
//        }
        solveWhite(_board);



    }
    static int a=0;
    private void solveWhite(char[][]_board){


        if(check(_board)) {
//            for(int k =0;k<rowMax;k++){
//                this.board[k]=_board[k].clone();
//            }
            GUI monitor2 = new GUI(this,_board);
            monitor2.setName("main");
            monitor2.setVisible(true);

            this.board = _board;


            return;}
        if(check(this.board))return;
        for(int i =0;i<rowMax;i++){
            for(int j=0;j<columnMax;j++){
                if(_board[i][j]=='w') {

                    char [][]newBoard1 = new char[rowMax][columnMax];
                    char [][]newBoard2 = new char[rowMax][columnMax];
                    for(int k =0;k<rowMax;k++){
                        newBoard1[k]=_board[k].clone();
                        newBoard2[k]=_board[k].clone();
                    }
                    changeTo(newBoard1, i, j, 'x');
                    solveWhite(newBoard1);
                    changeTo(newBoard2,i,j,'*');
                    solveWhite(newBoard2);

                }
            }
        }
        System.out.println(a++);






    }

    private void solveIt(char [][]_board) throws Exception
    {   if(check(_board))this.board = _board;
        if(deadpoint(_board)) return;
        solveDigital(_board);

        /*
        for(int i = 0;i < rowMax;i++){
            for(int j =0 ; j<columnMax;j++){
                if(board[i][j]=='w'){
                    changeTo(board,i,j,'x');
                    solveIt(board);
                    changeTo(board,i,j,'*');
                }
            }}
        */

    return;

    }
    public void solveIt(){
        Step1();
        try{solveIt(board);}catch (Exception e){
            e.printStackTrace();
        }
    }
    public boolean deployed(){
        try{
            File file = new File("puzzle");
            FileInputStream fis = new FileInputStream(file);
            InputStreamReader reader0  = new InputStreamReader(fis,"UTF-8");
            BufferedReader reader = new BufferedReader(reader0);
            for(int i = 0; i< rowMax; i++){
            String line = reader.readLine();
            String[] s = line.split(" ");
            for(int j = 0; j< columnMax; j++){
                char[] c = s[j].toCharArray();
                board[i][j]=c[0];
            }
            }

        }catch (IOException e){
            e.printStackTrace();
        }
        if(correctlyDeployed())
        {return true;}
        else {return false;}
    }
    private boolean correctlyDeployed(){
        return true;

    }

    public void printBoard(char [][] b){

        for(int i = 0; i < rowMax; i ++){
            for(int j = 0; j< rowMax; j ++) {
                System.out.print(board[i][j]+"  ");
            }
        System.out.println();
        }
        System.out.println();
    }

    public static void main(String args[]){
        try{
            Frames puzzle = new Frames(10,10);
            puzzle.solveIt();
//            GUI monitor = new GUI(puzzle);
//            monitor.setName("main");
//            monitor.setVisible(true);


            }
        catch (Exception e)
        {e.printStackTrace();}



    }

}

