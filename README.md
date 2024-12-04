<H1> COP3530 - Project 3: Recommendation Algorithms </h1>
This project consists of two algorithms for recommending videos on a video sharing service (i.e. YouTube).

<H2> Recommend By Popularity </h2>
This algorithm utilizes a binary heap tree to sort videos by view count, with the most views at the top of the tree.
The program takes in the data set of videos (Tik Kroks Data Set) and shows you the five most popular videos.

To "watch" a video:
1. Type 1 or 2 when prompted to search for a video by title or ID, respectively.
2. Enter the title/ID of the video you want to watch when prompted.
3. The video is now "watched" and its view count will increase by 1.

Note that, using the full data set of YouTube videos, it is very difficult to get a video to change ranks in the tree. For this reason, a second .csv file (Tik Kroks MOCK Data Set) has been provided that uses a few given values with low view counts to better demonstrate the heap tree's behavior after a video has been watched.
