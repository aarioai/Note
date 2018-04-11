/**
 * @see http://en.wikipedia.org/wiki/Class_diagram
 *  + public
 *   private
 *  # protected
 *  / derived
 *  ~ package
 * @note relationship from estrangement to inseparable
 *  Dependency < Association < Aggregation < Composition
 *  
 *  Generalization      ----|>
 *  Realization         - - -|>
 *  Association         ----->
 *  Aggregation         <>---->
 *  Composition         <<>>----> 
 *  Dependency          - - - ->
 */

 
 
 
class Juvenile { 
  /**
   * Association
   *  Juvenile has Tutors, Friends ...
   */
  list<Tutor> tutor; // Juvenile --------> Tutor
  /**
   * Aggregation: variant "has a" association relationship
   *  Juvenile is made up with adults(Men and women)
   */
  Menfolk men;            // Juvenile <>----------> Menfolk
  Women feminine[4];     // Juvenile <>-----------> Women
}

class Digest {
  virtual void drain() = 0;
}


class Digestive: public Juvenile,  // Generalization:  Digestive ----|> Juvenile
                 public Digest  // Realization:     Digestive - - - -|> Digest
{
  public:
  /**
   * Dependency: 
   *  you can digest Legume, Fruit ..., any food.
   */
  void digest(Legume legume); // Digestive - - - -> Legume
  /**
   * Composition: stronger variant "has a" association relationship, inseparable
   *  Without Digestive, Intestine, Stomach are worthless, they can't exist inde
   *  pendent.
   */
  Intestine Intestine;          // Digestive <<>>-----> Intestine
  Stomach stomach[3];         // Digestive <<>>------> Stomach
} 