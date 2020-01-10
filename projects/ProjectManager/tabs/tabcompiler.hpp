/**
 * @headerfile tabcompiler.hpp "tabcompiler.hpp"
 * @brief Description de la classe TabCompiler
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

    /**
     * @todo Faire l'onglet de compilation
     */

    #include "tab.hpp"

    namespace Ui {
        class TabCompiler;
    }

    /**
     * @class TabCompiler tabcompiler.hpp "tabcompiler.hpp"
     * @brief La classe TabCompiler défini l'onglet de compilation
     *
     * Elle permet avec de définir :
     * @li les options de compilation
     * @li des defines à appliquer à la compilation
     * @li les librairie à importer
     * @li le mode de compilation : release (défini NDEBUG) ou debug (défini _DEBUG)
     */
    class TabCompiler : public Tab
    {
        Q_OBJECT

        public:
            TabCompiler(QWidget *parent = nullptr);
            ~TabCompiler();
            /*void clean();
            QStringList getInfo();*/

        private:
            Ui::TabCompiler *ui;
    };

#endif // TABCOMPILER_HPP
