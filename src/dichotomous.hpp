//04/09/2010

#ifndef DICHOTOMOUS_H
#define DICHOTOMOUS_H

#include <vector>
#include <wx/string.h>
#include <wx/arrstr.h>

///\brief Classe template pour trier des données dans un ordre alphabétique.
///
///Le type de donner de cette classe DOIT être obligatoirement une classe avec au mien un attribut name en public de type wxString.
///
///ex :
///\code
///class data
///{
///    wxString name;
///    ...
///};
///\endcode
///
///L'algorithme de recherche, à été conçus de manier à se que la recherche s'effectue qu'une seule foi,
///lor de l'appelle successive à la méthode find(), pour la même donnée (name).
///
///Par exemple, les méthodes exist() et remove() font appelle à la méthode find(). On peux décider de faire appelle à la méthode exist() avec un "name"
///en paramètre. Celle ci va faire appelle à la methode find(), qui elle va sauvegarder la position de la recherche. Ensuit on appellent remove() avec
///le même "name" en paramètre qu'avec exist() que l'on à appeler précédemment. remove() va appeler find() qui elle va d'abord regarder si  la valeur
///quelle à sauvegarder précédemment n'est pas celle que l'on recherche. Ci c'est le ça l'algorithme n'ai pas lancer sinon l'algorithme et lancer
///pour faire la recherche.
template<typename T>
class dichotomous
{
    public:
        virtual ~dichotomous(void){}

        size_t size()const;
        bool isEmpty()const;
        bool exist(const wxString& name)const;
        void add(const T& data);
        bool rename(const wxString& newName, const wxString& name);
        bool remove(const wxString& name);
        void clear();
        wxArrayString getNames()const;
        const T& get(const wxString& name)const;
        const std::vector<T>& gets()const;

    protected:
        size_t find(wxString name)const;

        std::vector<T> m_datas;
};

/// \brief Permet d'obtenir le nombre de donnée dans la liste.
/// \return Retourne le nombre de donnée.
template<typename T>
size_t dichotomous<T>::size()const
{
    return m_datas.size();
}

/// \brief Permet de savoir si la lite est vide ou pas.
/// \return Retourne true si elle est fide sinon false.
template<typename T>
bool dichotomous<T>::isEmpty()const
{
    return m_datas.empty();
}

/// \brief Pour savoir si une donnée existe dans la liste.
///
/// \param name est la donnée à rechercher.
/// \return true si la donnée existe sinon false.
template<typename T>
bool dichotomous<T>::exist(const wxString& name)const
{
        size_t findId = find(name);
        if(m_datas.size() > findId)
        {
            if(m_datas[findId].name == name)
                return true;
        }

    return false;
}

/// \brief Ajout une donnée à la liste déjà existent.
///
/// \param data qui est la structure de donnée à ajouter.
template<typename T>
void dichotomous<T>::add(const T& data)
{
    m_datas.insert(m_datas.begin()+find(data.name), data);
}

/// \brief Renomme le nom d'une donnée.
///
/// \param newName est le nouveau nom.
/// \param name est le nom à renommer.
/// \return Renvoi true si la donner a bien été modifier, sinon false qui veut dire que la donnée n'existe pas.
template<typename T>
bool dichotomous<T>::rename(const wxString& newName, const wxString& name)
{
    T tmpData = m_datas[find(name)];

    if(!remove(name))
        return false;

    tmpData.name = newName;

    add(tmpData);

    return true;
}

/// \brief Supprime une donnée a la liste déjà existent.
///
/// \param name est la donnée à supprimer.
/// \return Renvoi true si la donner a bien été supprimer, sinon false qui veut dire que la donnée n'existe pas.
template<typename T>
bool dichotomous<T>::remove(const wxString& name)
{
    size_t id = find(name);

    if(m_datas[id].name == name)
    {
        m_datas.erase(m_datas.begin()+id);
        return true;
    }

    return false;
}

/// \brief Supprime touts les données de la liste.
template<typename T>
void dichotomous<T>::clear()
{
    m_datas.clear();
}

/// \brief Permet de connaître tout les nom.
/// \return renvoi touts les noms des données de la classe.
template<typename T>
wxArrayString dichotomous<T>::getNames()const
{
    wxArrayString tmpName;

    for(size_t i = 0; i < m_datas.size(); i++)
    {
        tmpName.Add(m_datas[i].name);
    }

    return tmpName;
}

/// \brief Permet d'accéder à la donner par son non (name).
///
/// \attention Avant d'utiliser cette fonction soyez sur que la donnée existe.
/// Ci la donnée n'a pas été trouver, une autre donnée peut être retourner. Ceci ne devrai pas arriver si vous êtes sur de l'existence de la donnée.
/// \param name est  la donnée rechercher.
/// \return renvoi la donnée rechercher.
template<typename T>
const T& dichotomous<T>::get(const wxString& name)const
{
    return m_datas[find(name)];
}

/// \brief Permet d'accéder à tout les données en une seul fois.
///
/// \return renvoi une référence constante de tous les données sou forme de std::vector<T>.
template<typename T>
const std::vector<T>& dichotomous<T>::gets()const
{
    return m_datas;
}

/// \brief Recherche une donner.
///Ou Recherche la position idéale pour une donnée.
///
/// \param name est le nom à rechercher ou à placer.
/// \return retourne la position de la donnée de la recherche, ou la position idéale, si l'algorithme n'a pas trouver la donnée.
template<typename T>
size_t dichotomous<T>::find(wxString name)const
{
    static size_t idPres = 0;

    if(m_datas.size() != 0)
    {
        if(idPres >= m_datas.size())
            idPres = 0;

        name.MakeLower();
        wxString namesLowerId = m_datas[idPres].name.Lower();

        if(namesLowerId != name)
        {
            bool stop = false;

            size_t idSup = m_datas.size();
            size_t idInf = 0;

            while(!stop)
            {
                idPres = (idInf+idSup)/2;

                namesLowerId = m_datas[idPres].name.Lower();
                if(namesLowerId == name || idInf+1 == idSup)
                {
                    if(namesLowerId < name)
                        idPres++;

                    stop = true;
                }
                else if(namesLowerId < name)
                    idInf = idPres;
                else
                    idSup = idPres;
            }
        }
    }
    else
        idPres = 0;

    return idPres;
}

#endif // DICHOTOMOUS_H
