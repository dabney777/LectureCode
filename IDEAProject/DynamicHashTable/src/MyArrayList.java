import org.omg.CORBA.Any;

/**
 * Created by Dabney on 10/17/2016.
 */
public class MyArrayList<AnyType> implements Iterable<AnyType> {
    private static final int DEFAULT_CAPACITY =10;

    private int theSize;
    private AnyType [] theItems ;
    public int size(){return theSize;}
    public boolean isEmpty(){
        return theSize==0;
    }
    public void clear(){
        theSize=0;
        ensureCapacity(DEFAULT_CAPACITY);
    }

    public AnyType get(int idx){
        if(idx>=theSize||idx<0)
            throw new ArrayIndexOutOfBoundsException();
        return theItems[idx];
    }
    public AnyType set(int idx,AnyType newVal){
        AnyType old =theItems[idx];
        theItems[idx]=newVal;
        return old;
    }
    public void add(int idx,AnyType x){
        if(theSize==theItems.length)
            ensureCapacity(theSize*2+1);
        for(int i = theSize;i>idx;i--){
            theItems[i]=theItems[i-1];
        }
        theItems[idx]=x;
        theSize++;

    }


    public void ensureCapacity(int newCapacity){
        if(newCapacity<theSize)
            return;
        AnyType [] old = theItems;
        theItems = (AnyType []) new Object[newCapacity];
        for(int i =0;i<theSize;i++){
            theItems[i]=theItems[i];
        }
    }

    public AnyType remove(int idx){
        AnyType old = theItems[idx];
        for(int i = idx;i<theSize;i--){
            theItems[i]=theItems[i+1];
        }
        theSize--;
        return old;
    }

    public java.util.Iterator<AnyType> iterator(){
        return new ArrayListIterator();


    }

    private class ArrayListIterator implements java.util.Iterator<AnyType>{
        private int current =0;

        public boolean hasNext(){
            return current <theSize;
        }
        public AnyType next(){
           if(!hasNext())throw new java.util.NoSuchElementException();
            return  theItems[current++];

        }
        public void remove(){
            MyArrayList.this.remove(--current);
        }
    }



}
