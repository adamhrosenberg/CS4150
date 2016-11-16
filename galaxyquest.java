//Adam Rosenberg
import java.util.Scanner;
import java.util.ArrayList
	
	
/**
		
		NASA recently confirmed the discovery of parallel universes (PUs) occupying alternate dimensions. These universes are quite different from our own universe, in the following ways:

		Each PU is a two-dimensional square that stretches 109109 light years from left to right and from top to bottom.
		Each PU has a galactic diameter of dd light years, where dd is an integer.
		Each star is exactly xx light years from its universe’s left edge and yy light years from its universe’s bottom edge, where xx and yy are non-negative integers.
		Stars are clustered into galaxies. Each galaxy consists of one or more stars. Each star is at most dd light years from every other star in its galaxy. Any two stars from different galaxies are more than dd light years apart.
		It is crucial to understand the implications of this. The locations of the stars determine the galaxies. The galaxy to which a star ss belongs consists of ss plus all other stars that are within dd light years of ss. Suppose you draw a circle of diameter dd around all of the stars of a galaxy. Any star not belonging to the galaxy will be outside the circle and will be more than dd light years from every star in the galaxy.
		For each PU, NASA has obtained all of its stellar coordinates and has measured its value of dd.

		Given the description of a PU, NASA would like to be able to determine whether that PU has a galaxy that contains more than half of the stars in the PU. NASA has turned to you.

		Input
		The input describes a single PU. All numbers in the input are integers.

		The first line of the input contains the PU’s galactic diameter dd (1≤d≤1061≤d≤106) and star count kk (1≤k≤1061≤k≤106).

		There are exactly kk more lines. Each line contains the xx (0≤x≤1090≤x≤109) and yy (0≤y≤1090≤y≤109) coordinates of a star in the PU. No two of these lines are identical, as a black hole would result!

		The star positions and dd are guaranteed to obey the clustering constraint discussed above.

		Output
		If the PU described by the input has a galaxy containing more than half of the stars, display the number of stars in that galaxy. Otherwise, display NO.
		
**/
	
	
	
class point{
	long x,y;
	point(long _x, long _y){
		x = _x;
		y = _y;
	}
}
class Galaxy{
	long hash;
	long x;
	long y;
	long numberofstars;
	point loc;
	Galaxy(point location){
		x = location.x;
		y = location.y;
		loc = location;
		numberofstars = 0;
		hash = (long)(Math.pow(location.x, 2) + Math.pow(location.y, 2));
	}

}
class node{
	node left;
	node right;
	Galaxy g;
}

class bst<galaxy>{
	node root;
	long numberofstars = 0;
	
	void insertgalaxy(Galaxy g){
		node nodetoadd = new node();
		nodetoadd.g =  g;
		boolean notdone = false;
		
		if(root == null){
			root = nodetoadd;
		}else{
			node currentnode = root;
			node parent;
			
			while(!notdone){
				parent = currentnode;
				if(g.hash < currentnode.g.hash){
					currentnode = currentnode.left;
					if(currentnode == null){
						parent.left = nodetoadd;
						notdone = true;
					}
				}else{
					currentnode = currentnode.right;
					if(currentnode == null){
						parent.right = nodetoadd;
						notdone = true;
					}
				}
			}
		}
		numberofstars++; //might be in wrong place.
	}
}



public class main {
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		long numberofstars;
		long maxcount;
		long d;
		bst<Galaxy> universe = new bst<Galaxy>();
		
		d = scanner.nextInt();
		numberofstars = scanner.nextInt();
		
		d = d*d;
		
		long x = scanner.nextInt();
		long y = scanner.nextInt();
		point pt = new point(x,y);
		
//		long currenthash = hash(pt.x,pt.y);
		Galaxy primarygalaxy = new Galaxy(pt);
		primarygalaxy.numberofstars++;
		universe.insertgalaxy(primarygalaxy);
		maxcount = primarygalaxy.numberofstars;
		
		for(int index = 0; index < numberofstars-1; index++){
			if(universe.numberofstars > numberofstars /2){
				break;
			}
			long curx = scanner.nextInt();
			long cury = scanner.nextInt();
			point currentPoint = new point(curx,cury);
			long currenthash = hash(currentPoint.x, currentPoint.y);
			boolean addflag = false;
			node current = universe.root;
			scan: while(current!=null){
				Galaxy currentgalaxy = current.g;
				long distance = distanceoftwopoints(currentPoint, currentgalaxy.loc);
				if(distance <= d){
					currentgalaxy.numberofstars++;
					addflag = true;
					if(currentgalaxy.numberofstars > maxcount){
						maxcount = currentgalaxy.numberofstars;
					}
					break scan;
				}else{
					if(currenthash < currentgalaxy.hash){
						current = current.left;
					}else{
						current = current.right;
					}
				}
			}
			
			if(!addflag){
				Galaxy toadd = new Galaxy(currentPoint);
				toadd.numberofstars++;
				universe.insertgalaxy(toadd);
			}
		}
		scanner.close();
		
		if(maxcount > numberofstars/2){
			System.out.println(maxcount);
		}else{
			System.out.println("NO");
		}
	}
	static long hash(long x, long y){
		return (long) (Math.pow(x, 2) + Math.pow(y, 2));
	}
	static long distanceoftwopoints(point first, point second){
		return (long) ((long)Math.pow(second.x-first.x,2) + Math.pow(second.y-first.y, 2));
	}

}
