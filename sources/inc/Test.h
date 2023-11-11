//
// Created by Antonin Jean on 11/11/2023.
//

#ifndef PROCEDURALGEN_TEST_H
#define PROCEDURALGEN_TEST_H

/**
 * @brief Class TEST
 */
class Test{
public:
    virtual ~Test();

public:
    /**
     * @brief The Test Class used for doxygen implementation
     * @param x int parameter
     * @param y int parameter
     */
    Test(int x, int y);

    /**
     * @brief Getter for the x field
     * @return an int
     */
    int getX() const;

    /**
     * @brief Setter for the x field
     * @param x
     */
    void setX(int x);

    /**
     * @brief Getter for the y field
     * @return
     */
    int getY() const;

    /**
     * @brief Setter for the y field
     * @param y
     */
    void setY(int y);

private:
    int x;
    int y;
};


#endif //PROCEDURALGEN_TEST_H
