#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat dojob(Mat &img)
{
	Mat r,c,d,b;
	b=(Mat_<double>(2,2) <<
			1,1,1,1);
	r=(Mat_<double>(2,2) <<
			1,1,
			-1,-1);
	c=(Mat_<double>(2,2) <<
			1,-1,
			1,-1);
	d=(Mat_<double>(2,2) <<
			1,-1,
			-1,1);
	Mat row,col,dia,blu;
	Mat temp,ans;
	Size size(img.cols/2,img.rows/2);
	filter2D(img,temp,CV_64F,r);
	resize(temp,row,size);
	filter2D(img,temp,CV_64F,c);
	resize(temp,col,size);
	filter2D(img,temp,CV_64F,d);
	resize(temp,dia,size);
	Mat t,tt;
	multiply(row,row,t);
	t.copyTo(tt);
	multiply(col,col,t);
	tt+=t;
	multiply(dia,dia,t);
	tt+=t;
	sqrt(t,ans);
	normalize(ans,ans,0,1,NORM_MINMAX);
	filter2D(img,temp,CV_64F,b);
	resize(temp,blu,size);
	blu.copyTo(img);
	img/=4;
	return ans;
}
void work(char *c)
{
	Mat img=imread(c,0),imm;
	img.copyTo(imm);
	//imshow("w",imm);
	/*
	namedWindow("w1",WINDOW_AUTOSIZE);
	namedWindow("w",WINDOW_AUTOSIZE);
	namedWindow("w2",WINDOW_AUTOSIZE);
	namedWindow("w3",WINDOW_AUTOSIZE);
	*/
	Mat t1,t2,t3;
	t1=dojob(img);
	Mat t;
	Size s(t1.cols/8,t1.rows/8);
	resize(t1,t,s);
	int i,j,k,l;
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+7;d.y=u.y+7;
		Rect R(u,d);
		Mat seg = t1(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t1);
	t2=dojob(img);
	Size s2(t2.cols/4,t2.rows/4);
	resize(t2,t,s2);
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+3;d.y=u.y+3;
		Rect R(u,d);
		Mat seg = t2(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t2); 
	
	t3=dojob(img);
	Size s3(t3.cols/2,t3.rows/2);
	resize(t3,t,s3);
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+1;d.y=u.y+1;
		Rect R(u,d);
		Mat seg = t3(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t3);
	//imshow("w1",t1);
	//imshow("w2",t2);
	//imshow("w3",t3);
	//Time to check
	//cout<<t1.rows<<" "<<t2.rows<<" "<<t3.rows<<endl;
	int da=0,gr=0,bl=0;
	for(i=0;i<t1.cols;i++)
	for(j=0;j<t1.rows;j++)
	{
		double p,q,r;
		p=t1.at<double>(Point(i,j))*255;
		q=t2.at<double>(Point(i,j))*255;
		r=t3.at<double>(Point(i,j))*255;
		if(p<30 && q<30 && r<30) continue;
	//	cerr<<"Edge detected"<<endl;
		if(p>q && q>r)da++;
		if(p<q && q<r)gr++;
		if(q>p && q>r)gr++;
		if(p<q && 30>p)bl++;
	}
	//cerr<<da<<" "<<gr<<" "<<bl<<endl;
	double per=da;per/=(da+gr);per*=100;
	double blur=bl;blur/=gr;blur*=100;
	cout<<per<<" "<<blur<<endl;
	waitKey(0);
}
int main()
{
	freopen("JPG.txt","r",stdin);
	char a[1500];int i=841;
	while(i--)
	{
		scanf("%s",a);	
		cerr<<841-i<<endl;
		work(a);
	}
	/*
	Mat img=imread("circle.jpeg",0),imm;
	img.copyTo(imm);
	*/
	//imshow("w",imm);
	/*
	namedWindow("w1",WINDOW_AUTOSIZE);
	namedWindow("w",WINDOW_AUTOSIZE);
	namedWindow("w2",WINDOW_AUTOSIZE);
	namedWindow("w3",WINDOW_AUTOSIZE);
	*/
	/*
	Mat t1,t2,t3;
	t1=dojob(img);
	Mat t;
	Size s(t1.cols/8,t1.rows/8);
	resize(t1,t,s);
	int i,j,k,l;
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+7;d.y=u.y+7;
		Rect R(u,d);
		Mat seg = t1(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t1);
	t2=dojob(img);
	Size s2(t2.cols/4,t2.rows/4);
	resize(t2,t,s2);
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+3;d.y=u.y+3;
		Rect R(u,d);
		Mat seg = t2(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t2); 
	
	t3=dojob(img);
	Size s3(t3.cols/2,t3.rows/2);
	resize(t3,t,s3);
	for(i=0;i<t.cols;i++)
	for(j=0;j<t.rows;j++)
	{
		Point u,d;
		u.x=j;u.y=i;
		d.x=u.x+1;d.y=u.y+1;
		Rect R(u,d);
		Mat seg = t3(R);
		double p=0,q=0;
		minMaxLoc(seg,&p,&q);
		t.at<uchar>(Point(i,j))=q;
	}
	t.copyTo(t3);
	//imshow("w1",t1);
	//imshow("w2",t2);
	//imshow("w3",t3);
	//Time to check
	cerr<<t1.rows<<" "<<t2.rows<<" "<<t3.rows<<endl;
	int da=0,gr=0,bl=0;
	for(i=0;i<t1.cols;i++)
	for(j=0;j<t1.rows;j++)
	{
		double p,q,r;
		p=t1.at<double>(Point(i,j))*255;
		q=t2.at<double>(Point(i,j))*255;
		r=t3.at<double>(Point(i,j))*255;
		if(p<30 && q<30 && r<30) continue;
	//	cerr<<"Edge detected"<<endl;
		if(p>q && q>r)da++;
		if(p<q && q<r)gr++;
		if(q>p && q>r)gr++;
		if(p<q && 30>p)bl++;
	}
	cerr<<da<<" "<<gr<<" "<<bl<<endl;
	double per=da;per/=(da+gr);per*=100;
	double blur=bl;blur/=gr;blur*=100;
	cerr<<per<<" "<<blur<<endl;
	waitKey(0);*/

}
