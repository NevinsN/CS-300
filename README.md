# CS-300
Repository for work in CS-300 DSA: Analysis and Design

In this course we dealt with and created programs that focused on data sctructures. I'm proud of what I got through this term.

What was the problem you were solving in the projects for this course?

For this course and program, we were looking to build a system that would efficiently handle ABCU's course catalogue utilizing the proper data structures in order to keep it useable, scalable, maintainable, and efficient.

How did you approach the problem? Consider why data structures are important to understand.

Approaching this issue was a two part thing for me. First, I recognized a lot of overlap with practice assignments we had throughout the term and was able to utilize the app structure found there to get me close to my final solution. Looking at the data structures available, it was clear to me that a binary search tree was going to be my best option. While loads could potentially be longer, the pre-sorted structure would make recall times neglible. It's absolutely vital to think about how the desired program will be used, how the data will be interacted with, and what part of data input and output is going to be the most utilized. Once you understand the uses for the program, it then is imperitive that you know what sort of a data structure will support those needs best to make the most informed and wise descisions for your app.

How did you overcome any roadblocks you encountered while going through the activities or project?

I recognized two roadblocks, one minor and one major. The minor roadblock was in the parsing. Originally, I was looking to cannabilize the CSVparser program we were provided, but the more I looked at and toyed with it, the more I realized that I would be better suited by making my own parser and keeping it a bit simpler. I did this, and it worked well for me. The major roadblock came with loading the parsed data into the binary search tree. It took multiple approaches, multiples attempts, and a lot of time to zero in on a working block of code. As I progressed, I encountered problems and needs that I hadn't anticipated, and needed to pivot in order to account for those use cases and needs that I hadn't thought to build into my plan. As I worked, I found my code got cleaner and more efficient, and I'm pretty happy with how all the work panned out.

How has your work on this project expanded your approach to designing software and developing programs?

The most important takeaway is building a c++ app essentially from scratch. The practice and experience were invaluable for giving me more confidence and familiarity with app development. I also appreciated how thoroughly it helped me understand not just data structures, but how to interact with them in efficient and applicable manners. It absolutely honed my ability to build and implement the logic that provides structure to every app.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project definitely gave me opportunities to focus on this aspect of development. By utilizing code from different sources to build out the bones of the app, it becomes readily apparent why readability is essential. This project gave me a great chance to practice thinking about how my code could be grown, how it would interact with any csv, or how it could be shifted or reused in other programs. It's also helpful to see that as code becomes more complicated to try and solve issues, as mine did initially, the best solution often really is to pare it down and keep it tight and streamlined. The fewest lines of code is best, and when I found myself with multiple nested loops, I began asking myself how could I shrink these loop layers? I think it led to a fairly polished model.
