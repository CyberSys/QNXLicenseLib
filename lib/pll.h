/*!
 * @file
 * @ingroup pll
 * @author  Александр Половцев (sasha_polo@mail.ru)
 * @date    30.05.2013 <BR>
 * @brief   Заголовочный файл, описывающий интерфейс библиотеки.
 *
 * @detail Данный файл описывает функции, реализующие функциональность,
 * заданную в техническом задании.
 */

#ifndef PLL_H_
#define PLL_H_

/*!
 * @brief  Размер буфера для MAC-адреса
 */
#define PLL_MAC_SIZE 6
/*!
 * @brief Размер открытого и проверочного ключей
 */
#define PLL_KEY_SIZE 16
/*!
 * @brief Количество символов в лицензии
 */
#define PLL_LICENSE_LEN 16

//! Функция для получения MAC-адреса
/*!
 * @ingroup pll
 *
 * @detail Функция, возвращающая MAC-адрес переданного интерфейса. Если
 * @p iface_name равен @c NULL, то функция вернет адрес первого интерфейса из списка
 * интерфейсов (удобно при генерации открытого ключа).
 *
 * @param [out] mac MAC-адрес
 * @param [in] iface_name имя интерфейса (или NULL)
 *
 * @retval 0 в случае успеха
 * @retval -2 если интерфейс не найден
 * @retval -1 в остальных случаях (при этом устанавливается переменная ERRNO)
 */
int pll_get_macaddr(char* mac, const char* iface_name);

//! Функция для получения серийного номера жесткого диска
/*!
 * @ingroup pll
 *
 * @param [out] serial серийный номер
 * @param [in] serial_len длина буфера @p serial, куда будет записан серийный номер
 * @param [in] hd_name путь к файлу жесткого диска
 *
 * @retval 0 в случае успеха
 * @retval -1 в остальных случаях (при этом устанавливается переменная ERRNO)
 *
 * Пример использования:
 * @code
 *     char serial[256];
 *     int err = pll_get_hdserial(serial, 256, "/dev/hd0");
 *     if (err) {
 *         perror("pll_get_hdserial");
 *         return EXIT_FAILURE;
 *     }
 *     printf("%s\n", serial);
 * @endcode
 */
int pll_get_hdserial(char* serial, size_t serial_len, const char* hd_name);

//! Функция для получения открытого ключа
/*!
 * @ingroup pll
 *
 * Функция, которая возвращает открытый ключ, основанный на информации
 * об аппаратных характеристиках компьютера. Предполагается, что размер буфера
 * @p key равен @c PLL_KEY_SIZE, иначе поведение функции не определено.
 *
 * @param [out] key открытый ключ
 *
 * @retval 0 в случае успеха
 * @retval -1 в остальных случаях (при этом устанавливается переменная ERRNO)
 */
int pll_get_open_key(char* key);

//! Функция для получения проверочного ключа
/*!
 * @ingroup pll
 *
 * Функция, которая возвращает проверочный ключ, основанный открытом ключе и лицензионном ключе.
 * Предполагается, что размер @p key и @p open_key равен @c PLL_KEY_SIZE,
 * иначе поведение функции не определено.
 *
 * @param [out] key проверочный ключ
 * @param [in] open_key открытый ключ
 * @param [in] license лицензионный ключ
 * @param [in] len размер лицензионного ключа
 *
 * @retval 0 в случае успеха
 * @retval -1 в остальных случаях (при этом устанавливается переменная ERRNO)
 */
int pll_get_check_key(char* key,
                      const char* open_key,
                      const char* license,
                      size_t len);

//! Функция для проверки соответствия лицензионного ключа определенному формату
/*!
 * @ingroup pll
 *
 * @param [in] license лицензионный ключ
 * @param [in] len размер лицензионного ключа
 *
 * @retval 0 если ключ соответствует формату
 * @retval -1 в противном случае
 */
int pll_parse_license(const char* license, size_t len);

#endif /* PLL_H_ */
