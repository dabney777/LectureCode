import com.sun.org.apache.bcel.internal.util.BCELifier;
import com.sun.org.apache.xpath.internal.operations.Number;

import java.util.ArrayList;
import java.io.*;


/**
 * Created by Dabney on 10/15/2016.
 */


public class HashTable {
    ArrayList<Bucket> hashList = new ArrayList();
    int currentBucketNum=2;
    private int numberOfInsertBucket(int hash){
        return hash%currentBucketNum;
    }
    public int hash(int key){
        return key*131313;
    }
    public void divide(){
        int old =currentBucketNum;
        currentBucketNum *=2;
        for(int i =old;i<currentBucketNum;i++){
            hashList.add(new Bucket());
        }

        for(int i=0;i < old;i++) {
            for (int j = 0; j < hashList.get(i).quantity; j++) {
                int newBucketNum=numberOfInsertBucket(hashList.get(i).key[j]);
                if ( newBucketNum== i) {
                } else {
                    hashList.get(newBucketNum).insert(hashList.get(i).key[j]);
                    hashList.get(i).key[j]=hashList.get(i).key[hashList.get(i).quantity--];
                    j--;
                }

            }
        }
        currentBucketNum *=2;
    }
    public void deleteKeyInbucket(int _key,int bucketNum){
        for (int j = 0; j < hashList.get(bucketNum).quantity; j++){
            if(hashList.get(bucketNum).key[j]==_key){
            hashList.get(bucketNum).key[j]=hashList.get(bucketNum).key[hashList.get(bucketNum).quantity--];
            }
        }

    }
    public void insert(int key){
        if(hashList.get(numberOfInsertBucket(key)).insert(key)!=true){
            divide();
            insert(key);
        }
    }
    public void deleteKey(int _key){
        deleteKeyInbucket(_key,numberOfInsertBucket(hash(_key)));
    }



    public static void main(String[] args) {
      /*  HashTable hashTable=new HashTable();
        for(int i =0;i<1000;i++){
            hashTable.insert(i);
        }
        int a=0;

       File file1 = new File(".\\text.txt");
        File file2 = new File(".\\origin.txt");
        if(file1.exists()){
        }else{
            try {
                file1.createNewFile();
            }catch(IOException e){
                e.printStackTrace();
            }
        }
        char[] a=new char[1000000000];

        try{
            FileWriter writer = new FileWriter(file2);
            FileReader reader = new FileReader(file1);
            reader.read(a);
            String ss=new String(a);
            String[] b=ss.split(" ");
            reader.close();
            int n =Integer.parseInt(b[0]);
            for(int i = 1;i<n+1;i++){
                hashTable.hashList.add( new Bucket( Integer.parseInt(b[i]) ) );
            }
            hashTable.hashList.remove(1);
            System.out.print(hashTable.hashList.get(1).key[0]);
        }catch(IOException e){
            e.printStackTrace();
        }catch(NumberFormatException e){
            e.printStackTrace();
        }

*/
    }




}
