#ifndef SFML_HELPER_H
#define SFML_HELPER_H

#include <SFML/Graphics.hpp>

class SFML_Helper
{
    public:
        /** Default constructor */
        SFML_Helper();
        /** Access *mainWindow
         * \return The current value of *mainWindow
         */
        sf::RenderWindow* GetmainWindow() { return mainWindow; }
    protected:
    private:
        sf::RenderWindow *mainWindow; //!< Member variable "*mainWindow"
};

#endif // SFML_HELPER_H
