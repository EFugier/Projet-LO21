#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H

#include "qttools.h"
#include <QMovie>

/// @class MatrixController
class MatrixController : public QTableWidget{
  Q_OBJECT

    friend class MainController;

    QMovie *movie;
    QMovie *movie2;
    bool anim;
    dim dimension;
    int index;
public:

    /**
     * \fn MatrixController(int c, int r, QWidget* p)
     * \brief Constructeur du MatrixController. Création d'une matrice et réajustement de sa taille dans la fenêtre.
     *
     * \param c nombre de colonnes de la matrice
     *  \param r nombre de lignes de la matrice
    */
    MatrixController(int column, int rows=1, QWidget* parent=nullptr);

    /**
     * \fn std::vector<bool> serializeGrid()
     * \brief Méthode de sérialisation de la grille en booléens
     *
     * \param vect vecteur de booléens
    */
    std::vector<bool> serializeGrid();
    std::vector<bool> serializeGrid(bool v);
    void switchBool() { anim = !anim; }
    bool getAnim() const { return anim; }

    /**
     * \fn void onChangeD1(std::vector<bool>& v)
     * \brief Fonction de mise à jour de la vue 1D
     *
     * \param v vecteur de booléens calculés par le modèle contenant la séquence de cellules à afficher
    */
    void onChangeD1(std::vector<bool>& v);

    /**
     * \fn void onChangeD2(std::vector<bool>& v)
     * \brief Fonction de mise à jour de la vue 2D
     *
     * \param v vecteur de booléens calculés par le modèle contenant la séquence de cellules à afficher
    */
    void onChangeD2(std::vector<bool>& v);
    void setDimension(dim d) { dimension = d; index = 0; }
    dim getDimension() const { return dimension; }
private slots:

    /**
     * \fn void onChange(std::vector<bool>& v)
     * \brief Slot de la classe MatrixController servant à la mise à jour de l'affichage en fonction du modèle.
     *  La fonction redirige vers la méthode d'affichage correspondante selon si l'automate est 1D ou 2D
     *
     * \param v vecteur de booléens calculés par le modèle contenant la séquence de cellules à afficher
    */
    void onChange(std::vector<bool>& v);

    /**
     * \fn void cellActivation(QModelIndex index)
     * \brief Slot de la classe MatrixController servant à réagir au clic de l'utilsateur dans la matrice.
     *  La cellule cliquée dont l'indice est transmis en paramètre, voit sa couleur passer du noir au blanc.
     *
     * \param index indice de la cellule courante lors du clic
    */
    void cellActivation(QModelIndex);
};



#endif // MATRIXCONTROLLER_H


