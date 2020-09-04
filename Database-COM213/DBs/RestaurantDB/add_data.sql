  ---------------------------Sections----------------

INSERT INTO Sections Values(1, 'Salad')
INSERT INTO Sections Values(2, 'Soup')
INSERT INTO Sections Values(3, 'Hot dish')
INSERT INTO Sections Values(4, 'Snack')
INSERT INTO Sections Values(5, 'Drink')
INSERT INTO Sections Values(6, 'Desert')
INSERT INTO Sections Values(7, 'Garnish')
;
---------------------------Dishes----------------

INSERT INTO Dishes Values(1, 'British salad', 1, 250)
INSERT INTO Dishes Values(2, 'Warm chicken salad', 1, 350)
INSERT INTO Dishes Values(3, 'Caesar salad', 1, 300)
INSERT INTO Dishes Values(4, 'House salad', 1, 200)
INSERT INTO Dishes Values(5, 'Summer salad', 1, 250)
INSERT INTO Dishes Values(6, 'Wild mushroom soup', 2, 250)
INSERT INTO Dishes Values(7, 'Chicken soup', 2, 300)
INSERT INTO Dishes Values(8, 'Spisy soup', 2, 250)
INSERT INTO Dishes Values(9, 'Seafood soup', 2, 400)
INSERT INTO Dishes Values(10, 'Kharcho soup', 2, 300)
INSERT INTO Dishes Values(11, 'Spisy tomato soup', 2, 300)
INSERT INTO Dishes Values(12, 'Turkey shank', 3, 1000)
INSERT INTO Dishes Values(13, 'Steak on the grill', 3, 500)
INSERT INTO Dishes Values(14, 'Pork ribs', 3, 500)
INSERT INTO Dishes Values(15, 'Filt mignon', 3, 400)
INSERT INTO Dishes Values(16, 'Burrito', 3, 400)
INSERT INTO Dishes Values(17, 'Salmon steak', 3, 400)
INSERT INTO Dishes Values(18, 'Hinkali', 3, 300)
INSERT INTO Dishes Values(19, 'JR.Fish', 3, 200)
INSERT INTO Dishes Values(20, 'JR.Burger', 3, 300)
INSERT INTO Dishes Values(21, 'JR.Pizza', 3, 250)
INSERT INTO Dishes Values(22, 'Burger', 3, 300)
INSERT INTO Dishes Values(23, 'Fajitas', 4, 300)
INSERT INTO Dishes Values(24, 'Spicy potato', 4, 200)
INSERT INTO Dishes Values(25, 'Calamari rings', 4, 250)
INSERT INTO Dishes Values(26, 'Rye garlic', 4, 200)
INSERT INTO Dishes Values(27, 'Croutons with cheese', 4, 400)
INSERT INTO Dishes Values(28, 'Old English pie', 6, 150)
INSERT INTO Dishes Values(29, 'Brownie', 6, 200)
INSERT INTO Dishes Values(30, 'Cheesecake', 6, 150)
INSERT INTO Dishes Values(31, 'Ice cream', 6, 200)
INSERT INTO Dishes Values(32, 'Sweet pancakes', 6, 250)
INSERT INTO Dishes Values(33, 'French fries', 7, 150)
INSERT INTO Dishes Values(34, 'Rice', 7, 200)
INSERT INTO Dishes Values(35, 'Vegetables', 7, 150)
INSERT INTO Dishes Values(36, 'Crockers potato', 7, 300)
INSERT INTO Dishes Values(37, 'Cider', 5, 250)
INSERT INTO Dishes Values(38, 'Beer', 5, 500)
INSERT INTO Dishes Values(39, 'Tea', 5, 500)
INSERT INTO Dishes Values(40, 'Coffee', 5, 200)
INSERT INTO Dishes Values(41, 'Juice', 5, 250)
INSERT INTO Dishes Values(42, 'Water', 5, 250)
INSERT INTO Dishes Values(43, 'Tonic', 5, 200)
INSERT INTO Dishes Values(44, 'Johnnie Walker', 5, 50)
INSERT INTO Dishes Values(45, 'Jameson', 5, 50)
INSERT INTO Dishes Values(46, 'Chivas Regal', 5, 50)
INSERT INTO Dishes Values(47, 'Captain Morgan', 5, 50)
INSERT INTO Dishes Values(48, 'Sumbuca', 5, 50)
INSERT INTO Dishes Values(49, 'Baileys', 5, 50)
INSERT INTO Dishes Values(50, 'Puer tea', 5, 500)
INSERT INTO Dishes Values(51, 'Milk oolong tea', 5, 500)
INSERT INTO Dishes Values(52, 'Lemonade', 5, 500)
INSERT INTO Dishes Values(53, 'Ice tea', 5, 50)
;

--------------------------Tags----------------------------

INSERT INTO Tags Values(1, 'Spicy')
INSERT INTO Tags Values(2, 'Vegetarian')
INSERT INTO Tags Values(3, 'Nonalcoholic')
INSERT INTO Tags Values(4, 'Cold')
INSERT INTO Tags Values(5, 'Grill')
INSERT INTO Tags Values(6, 'Kids')
;

-----------------------DishesTags------------------------------------

INSERT INTO DishesTags Values(1, 8, 1)
INSERT INTO DishesTags Values(2, 11, 1)
INSERT INTO DishesTags Values(3, 14, 1)
INSERT INTO DishesTags Values(4, 10, 4)
INSERT INTO DishesTags Values(5, 19, 6)
INSERT INTO DishesTags Values(6, 20, 6)
INSERT INTO DishesTags Values(7, 21, 6)
INSERT INTO DishesTags Values(8, 24, 1)
INSERT INTO DishesTags Values(9, 25, 5)
INSERT INTO DishesTags Values(10, 13, 5)
INSERT INTO DishesTags Values(11, 17, 5)
INSERT INTO DishesTags Values(12, 23, 1)
INSERT INTO DishesTags Values(13, 27, 6)
INSERT INTO DishesTags Values(14, 28, 6)
INSERT INTO DishesTags Values(15, 29, 6)
INSERT INTO DishesTags Values(16, 30, 6)
INSERT INTO DishesTags Values(17, 31, 6)
INSERT INTO DishesTags Values(18, 32, 6)
INSERT INTO DishesTags Values(19, 33, 6)
INSERT INTO DishesTags Values(20, 34, 6)
INSERT INTO DishesTags Values(21, 35, 6)
INSERT INTO DishesTags Values(22, 36, 6)
INSERT INTO DishesTags Values(23, 39, 3)
INSERT INTO DishesTags Values(24, 40, 3)
INSERT INTO DishesTags Values(25, 41, 3)
INSERT INTO DishesTags Values(26, 42, 3)
INSERT INTO DishesTags Values(27, 43, 3)
INSERT INTO DishesTags Values(28, 50, 3)
INSERT INTO DishesTags Values(29, 51, 3)
INSERT INTO DishesTags Values(30, 52, 4)
INSERT INTO DishesTags Values(31, 53, 4)
INSERT INTO DishesTags Values(32, 4, 4)
INSERT INTO DishesTags Values(33, 5, 4)
INSERT INTO DishesTags Values(34, 4, 2)
INSERT INTO DishesTags Values(35, 5, 2)
INSERT INTO DishesTags Values(36, 6, 2)
INSERT INTO DishesTags Values(37, 11, 2)
INSERT INTO DishesTags Values(38, 24, 2)
INSERT INTO DishesTags Values(39, 26, 2)
INSERT INTO DishesTags Values(40, 27, 2)
INSERT INTO DishesTags Values(41, 34, 2)
INSERT INTO DishesTags Values(42, 35, 2)
INSERT INTO DishesTags Values(43, 12, 2)
;
-----------------------Ingredients----------------------------------

INSERT INTO Ingredients Values(1, 'Onion')
INSERT INTO Ingredients Values(2, 'Carrot')
INSERT INTO Ingredients Values(3, 'Potato')
INSERT INTO Ingredients Values(4, 'Butter')
INSERT INTO Ingredients Values(5, 'Ham')
INSERT INTO Ingredients Values(6, 'Flour')
INSERT INTO Ingredients Values(7, 'Milk')
INSERT INTO Ingredients Values(8, 'Sugar')
INSERT INTO Ingredients Values(9, 'Egg')
INSERT INTO Ingredients Values(10, 'Beef')
INSERT INTO Ingredients Values(11, 'Pepper')
INSERT INTO Ingredients Values(12, 'Sausage')
INSERT INTO Ingredients Values(13, 'Lettuce leaves')
INSERT INTO Ingredients Values(14, 'Bread')
INSERT INTO Ingredients Values(15, 'Fish')
INSERT INTO Ingredients Values(16, 'Mushroom')
INSERT INTO Ingredients Values(17, 'Shrimp')
INSERT INTO Ingredients Values(18, 'Cheese')
INSERT INTO Ingredients Values(19, 'Beans')
INSERT INTO Ingredients Values(20, 'Tomato')
INSERT INTO Ingredients Values(21, 'Cucumber')
INSERT INTO Ingredients Values(22, 'Chicken')
INSERT INTO Ingredients Values(23, 'Pork')
INSERT INTO Ingredients Values(24, 'Oil')
INSERT INTO Ingredients Values(25, 'Turkey')
INSERT INTO Ingredients Values(26, 'Rice')
;

-----------------------Prices----------------------------------

INSERT INTO Prices Values(1, 1, NULL, NULL, 400)
INSERT INTO Prices Values(2, 2, NULL, NULL, 300)
INSERT INTO Prices Values(3, 3, NULL, NULL, 350)
INSERT INTO Prices Values(4, 4, '2018-05-01', '2018-10-31', 200)
INSERT INTO Prices Values(5, 5, '2018-05-01', '2018-10-31', 250)
INSERT INTO Prices Values(6, 6, '2018-05-01', '2018-10-31', 400)
INSERT INTO Prices Values(7, 7, NULL, NULL, 300)
INSERT INTO Prices Values(8, 8, NULL, NULL, 350)
INSERT INTO Prices Values(9, 9, NULL, NULL, 600)
INSERT INTO Prices Values(10, 10, NULL, NULL, 250)
INSERT INTO Prices Values(11, 11, '2018-05-01', '2018-10-31', 400)
INSERT INTO Prices Values(12, 12, NULL, NULL, 2000)
INSERT INTO Prices Values(13, 13, NULL, NULL, 600)
INSERT INTO Prices Values(14, 14, NULL, NULL, 750)
INSERT INTO Prices Values(15, 15, NULL, NULL, 500)
INSERT INTO Prices Values(16, 16, NULL, NULL, 850)
INSERT INTO Prices Values(17, 17, NULL, NULL, 600)
INSERT INTO Prices Values(18, 18, NULL, NULL, 650)
INSERT INTO Prices Values(19, 19, NULL, NULL, 350)
INSERT INTO Prices Values(20, 20, NULL, NULL, 300)
INSERT INTO Prices Values(21, 21, NULL, NULL, 350)
INSERT INTO Prices Values(22, 22, NULL, NULL, 400)
INSERT INTO Prices Values(23, 23, NULL, NULL, 300)
INSERT INTO Prices Values(24, 24, NULL, NULL, 350)
INSERT INTO Prices Values(25, 25, NULL, NULL, 400)
INSERT INTO Prices Values(26, 26, NULL, NULL, 300)
INSERT INTO Prices Values(27, 27, NULL, NULL, 350)
INSERT INTO Prices Values(28, 28, NULL, NULL, 200)
INSERT INTO Prices Values(29, 29, NULL, NULL, 220)
INSERT INTO Prices Values(30, 30, NULL, NULL, 280)
INSERT INTO Prices Values(31, 31, NULL, NULL, 270)
INSERT INTO Prices Values(32, 32, NULL, NULL, 220)
INSERT INTO Prices Values(33, 33, NULL, NULL, 150)
INSERT INTO Prices Values(34, 34, NULL, NULL, 120)
INSERT INTO Prices Values(35, 35, '2018-05-01', '2018-10-31', 150)
INSERT INTO Prices Values(36, 36, '2018-05-01', '2018-10-31', 120)
INSERT INTO Prices Values(37, 37, NULL, NULL, 200)
INSERT INTO Prices Values(38, 38, NULL, NULL, 300)
INSERT INTO Prices Values(39, 39, NULL, NULL, 200)
INSERT INTO Prices Values(40, 40, NULL, NULL, 300)
INSERT INTO Prices Values(41, 41, NULL, NULL, 150)
INSERT INTO Prices Values(42, 42, NULL, NULL, 140)
INSERT INTO Prices Values(43, 43, NULL, NULL, 130)
INSERT INTO Prices Values(44, 44, NULL, NULL, 470)
INSERT INTO Prices Values(45, 45, NULL, NULL, 300)
INSERT INTO Prices Values(46, 46, NULL, NULL, 350)
INSERT INTO Prices Values(47, 47, NULL, NULL, 260)
INSERT INTO Prices Values(48, 48, NULL, NULL, 320)
INSERT INTO Prices Values(49, 49, NULL, NULL, 300)
INSERT INTO Prices Values(50, 50, NULL, NULL, 280)
INSERT INTO Prices Values(51, 51, NULL, NULL, 280)
INSERT INTO Prices Values(52, 52, '2018-05-01', '2018-10-31', 320)
INSERT INTO Prices Values(53, 53, NULL, NULL, 270)
INSERT INTO Prices Values(54, 4, '2018-11-01', '2019-04-30', 300)
INSERT INTO Prices Values(55, 5, '2018-11-01', '2019-04-30', 350)
INSERT INTO Prices Values(56, 35, '2018-11-01', '2019-04-30', 250)
INSERT INTO Prices Values(57, 36, '2018-11-01', '2019-04-30', 220)
INSERT INTO Prices Values(58, 52, '2018-11-01', '2019-04-30', 420)
INSERT INTO Prices Values(59, 11, '2018-11-01', '2019-04-30', 500)
INSERT INTO Prices Values(60, 6, '2018-11-01', '2019-04-30', 500)

---------------------DishesIngredients--------------------------------

INSERT INTO DishesIngredients Values(1, 1, 1, 30)
INSERT INTO DishesIngredients Values(2, 1, 16, 50)
INSERT INTO DishesIngredients Values(3, 1, 22, 90)
INSERT INTO DishesIngredients Values(4, 1, 21, 80)
INSERT INTO DishesIngredients Values(5, 2, 22, 100)
INSERT INTO DishesIngredients Values(6, 2, 24, 110)
INSERT INTO DishesIngredients Values(7, 2, 18, 50)
INSERT INTO DishesIngredients Values(8, 2, 3, 90)
INSERT INTO DishesIngredients Values(9, 3, 9, 70)
INSERT INTO DishesIngredients Values(10, 3, 13, 70)
INSERT INTO DishesIngredients Values(11, 3, 17, 70)
INSERT INTO DishesIngredients Values(12, 3, 20, 40)
INSERT INTO DishesIngredients Values(13, 3, 14, 45)
INSERT INTO DishesIngredients Values(14, 3, 24, 5)
INSERT INTO DishesIngredients Values(15, 4, 1, 10)
INSERT INTO DishesIngredients Values(16, 4, 2, 50)
INSERT INTO DishesIngredients Values(17, 4, 3, 50)
INSERT INTO DishesIngredients Values(18, 4, 9, 40)
INSERT INTO DishesIngredients Values(19, 4, 11, 50)
INSERT INTO DishesIngredients Values(20, 5, 11, 100)
INSERT INTO DishesIngredients Values(21, 5, 20, 90)
INSERT INTO DishesIngredients Values(22, 5, 21, 50)
INSERT INTO DishesIngredients Values(23, 5, 24, 10)
INSERT INTO DishesIngredients Values(24, 6, 1, 10)
INSERT INTO DishesIngredients Values(25, 6, 2, 90)
INSERT INTO DishesIngredients Values(26, 6, 3, 90)
INSERT INTO DishesIngredients Values(27, 6, 16, 60)
INSERT INTO DishesIngredients Values(28, 7, 1, 80)
INSERT INTO DishesIngredients Values(29, 7, 2, 70)
INSERT INTO DishesIngredients Values(30, 7, 3, 50)
INSERT INTO DishesIngredients Values(31, 7, 22, 100)
INSERT INTO DishesIngredients Values(32, 8, 3, 50)
INSERT INTO DishesIngredients Values(33, 8, 11, 50)
INSERT INTO DishesIngredients Values(34, 8, 18, 50)
INSERT INTO DishesIngredients Values(35, 8, 19, 100)
INSERT INTO DishesIngredients Values(36, 9, 2, 100)
INSERT INTO DishesIngredients Values(37, 9, 7, 100)
INSERT INTO DishesIngredients Values(38, 9, 9, 100)
INSERT INTO DishesIngredients Values(39, 9, 17, 100)
INSERT INTO DishesIngredients Values(40, 10, 1, 10)
INSERT INTO DishesIngredients Values(41, 10, 2, 90)
INSERT INTO DishesIngredients Values(42, 10, 3, 100)
INSERT INTO DishesIngredients Values(43, 10, 5, 100)
INSERT INTO DishesIngredients Values(44, 11, 19, 50)
INSERT INTO DishesIngredients Values(45, 11, 18, 100)
INSERT INTO DishesIngredients Values(46, 11, 20, 50)
INSERT INTO DishesIngredients Values(47, 11, 3, 100)
INSERT INTO DishesIngredients Values(48, 12, 25, 1000)
INSERT INTO DishesIngredients Values(49, 13, 10, 500)
INSERT INTO DishesIngredients Values(50, 14, 22, 500)
INSERT INTO DishesIngredients Values(51, 15, 10, 300)
INSERT INTO DishesIngredients Values(52, 15, 11, 100)
INSERT INTO DishesIngredients Values(53, 16, 18, 100)
INSERT INTO DishesIngredients Values(54, 16, 19, 100)
INSERT INTO DishesIngredients Values(55, 16, 20, 100)
INSERT INTO DishesIngredients Values(56, 16, 22, 100)
INSERT INTO DishesIngredients Values(57, 17, 11, 40)
INSERT INTO DishesIngredients Values(58, 17, 20, 100)
INSERT INTO DishesIngredients Values(59, 17, 24, 10)
INSERT INTO DishesIngredients Values(60, 17, 15, 250)
INSERT INTO DishesIngredients Values(61, 18, 1, 50)
INSERT INTO DishesIngredients Values(62, 18, 6, 50)
INSERT INTO DishesIngredients Values(63, 18, 7, 50)
INSERT INTO DishesIngredients Values(64, 18, 8, 50)
INSERT INTO DishesIngredients Values(65, 18, 9, 50)
INSERT INTO DishesIngredients Values(66, 18, 10, 50)
INSERT INTO DishesIngredients Values(67, 19, 4, 50)
INSERT INTO DishesIngredients Values(68, 19, 10, 50)
INSERT INTO DishesIngredients Values(69, 19, 14, 50)
INSERT INTO DishesIngredients Values(70, 19, 15, 30)
INSERT INTO DishesIngredients Values(71, 19, 13, 20)
INSERT INTO DishesIngredients Values(72, 20, 13, 100)
INSERT INTO DishesIngredients Values(73, 20, 18, 50)
INSERT INTO DishesIngredients Values(74, 20, 20, 70)
INSERT INTO DishesIngredients Values(75, 20, 10, 80)
INSERT INTO DishesIngredients Values(76, 21, 5, 30)
INSERT INTO DishesIngredients Values(77, 21, 6, 20)
INSERT INTO DishesIngredients Values(78, 21, 7, 40)
INSERT INTO DishesIngredients Values(79, 21, 8, 40)
INSERT INTO DishesIngredients Values(80, 21, 9, 20)
INSERT INTO DishesIngredients Values(81, 21, 12, 40)
INSERT INTO DishesIngredients Values(82, 21, 18, 40)
INSERT INTO DishesIngredients Values(83, 21, 20, 50)
INSERT INTO DishesIngredients Values(84, 22, 14, 40)
INSERT INTO DishesIngredients Values(85, 22, 18, 40)
INSERT INTO DishesIngredients Values(86, 22, 20, 50)
INSERT INTO DishesIngredients Values(87, 22, 10, 80)
INSERT INTO DishesIngredients Values(88, 22, 13, 90)
INSERT INTO DishesIngredients Values(89, 23, 19, 80)
INSERT INTO DishesIngredients Values(90, 23, 20, 80)
INSERT INTO DishesIngredients Values(91, 23, 21, 80)
INSERT INTO DishesIngredients Values(92, 23, 22, 60)
INSERT INTO DishesIngredients Values(93, 24, 20, 150)
INSERT INTO DishesIngredients Values(94, 24, 11, 50)
INSERT INTO DishesIngredients Values(95, 25, 6, 50)
INSERT INTO DishesIngredients Values(96, 25, 9, 50)
INSERT INTO DishesIngredients Values(97, 25, 15, 150)
INSERT INTO DishesIngredients Values(98, 26, 4, 30)
INSERT INTO DishesIngredients Values(99, 26, 9, 20)
INSERT INTO DishesIngredients Values(100, 26, 14, 150)
INSERT INTO DishesIngredients Values(101, 27, 4, 50)
INSERT INTO DishesIngredients Values(102, 27, 14, 250)
INSERT INTO DishesIngredients Values(103, 27, 18, 100)
INSERT INTO DishesIngredients Values(104, 28, 4, 20)
INSERT INTO DishesIngredients Values(105, 28, 6, 30)
INSERT INTO DishesIngredients Values(106, 28, 7, 20)
INSERT INTO DishesIngredients Values(107, 28, 8, 30)
INSERT INTO DishesIngredients Values(108, 28, 9, 50)
INSERT INTO DishesIngredients Values(109, 29, 4, 50)
INSERT INTO DishesIngredients Values(110, 29, 5, 50)
INSERT INTO DishesIngredients Values(111, 29, 8, 50)
INSERT INTO DishesIngredients Values(112, 29, 9, 50)
INSERT INTO DishesIngredients Values(113, 30, 4, 20)
INSERT INTO DishesIngredients Values(114, 30, 6, 30)
INSERT INTO DishesIngredients Values(115, 30, 9, 50)
INSERT INTO DishesIngredients Values(116, 30, 18, 50)
INSERT INTO DishesIngredients Values(117, 31, 7, 100)
INSERT INTO DishesIngredients Values(118, 31, 8, 100)
INSERT INTO DishesIngredients Values(119, 31, 8, 50)
INSERT INTO DishesIngredients Values(120, 32, 4, 50)
INSERT INTO DishesIngredients Values(121, 32, 7, 50)
INSERT INTO DishesIngredients Values(122, 32, 6, 50)
INSERT INTO DishesIngredients Values(123, 32, 8, 50)
INSERT INTO DishesIngredients Values(124, 32, 9, 50)
INSERT INTO DishesIngredients Values(125, 33, 3, 150)
INSERT INTO DishesIngredients Values(126, 34, 26, 200)
INSERT INTO DishesIngredients Values(127, 35, 2, 40)
INSERT INTO DishesIngredients Values(128, 35, 11, 40)
INSERT INTO DishesIngredients Values(129, 35, 16, 40)
INSERT INTO DishesIngredients Values(130, 35, 20, 30)
INSERT INTO DishesIngredients Values(131, 36, 3, 300)
;


