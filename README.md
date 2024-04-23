# USCoursefit

USCoursefit is a scheduling application designed specifically for USC students to schedule desired courses and avoid time conflicts.

<p align="center">
  <img src="logo.png" width="300" alt="description">
</p>

## Functionality

This application allows USC students to input their desired courses and generates a schedule that avoids any time conflicts between them. It streamlines the course selection process and ensures that students can plan their academic terms more effectively.

## Files Included

- **CourseSection.h**: Contains three C++ classes with corresponding functions that represent course information, section information, and a list of courses.
- **CourseSection.cpp**: Implements the functions defined in `CourseSection.h`.
- **application.cpp**: This file contains the `main()` function. It prompts the user to input specific information about courses and generates the desired schedule based on the inputs.
- **sampleInput.txt**: A sample input file that users can use to test the application in the terminal.

## Terminal Commands for Compilation and Running

To compile the application, please ensure you have downloaded `CourseSection.h`, `CourseSection.cpp`, and `application.cpp`. Use the following command in your terminal to compile the code:

`g++ -g application.cpp -o application`

To run the executable file, use the command:

`./application`

## Limitations and Future Improvements

1. **Enabling File Streams**: Allow users to input data from files rather than typing manually, which would streamline the data entry process.
2. **Handling Special Course Requirements**: Currently, the application does not support specific requirements of certain courses, such as mandatory discussions linked to specific lectures. Future versions will address this limitation.
3. **Offering More User Options**: Future updates will include more flexible scheduling options, such as minimizing class times on specific days (e.g., Fridays).

## Contact

If you have any concerns or valuable advice, please feel free to contact me at: 
- **Email**: [Xinyangxu-2023@outlook.com](mailto:Xinyangxu-2023@outlook.com)

## Credit

- **Developer**: Xinyang Xu

Feel free to fork this repository, contribute to its development, or use it as a reference for your own projects!

