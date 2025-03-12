El HAL (***Hardware Abstraction Layer*** o Capa de Abstracción de Hardware) del ESP32 es una parte fundamental del ESP-IDF (*Espressif IoT Development Framework*), que es el entorno de desarrollo oficial para los microcontroladores ESP32. El HAL proporciona una interfaz de programación que abstrae los detalles específicos del hardware, permitiendo a los desarrolladores trabajar a un nivel más alto sin preocuparse de los detalles de bajo nivel de los registros y periféricos.
## Estructura del HAL de ESP32: Componentes principales

El HAL de ESP32 se organiza en módulos o componentes que corresponden a diferentes periféricos y subsistemas:

1. **Drivers de periféricos**:
    - GPIO
    - SPI
    - I2C
    - UART
    - ADC/DAC
    - PWM (LEDC)
    - Timers
    - RTC
    - Ethernet
    - CAN
2. **Subsistemas**:
    - Wi-Fi
    - Bluetooth
    - Sistema de archivos (SPIFFS, FAT)
    - Gestión de energía
3. **Utilidades**:
    - Manejo de eventos
    - Gestión de memoria
    - Sincronización

## Características principales del HAL

### 1. Abstracción del hardware

El HAL oculta los detalles específicos del hardware y proporciona funciones fáciles de usar. Por ejemplo, en lugar de manipular directamente registros para configurar un pin GPIO:
```cpp
// Sin HAL, manipulación directa de registros
GPIO.enable_w1ts = (1 << GPIO_NUM_2);
GPIO.out_w1ts = (1 << GPIO_NUM_2);

// Con HAL
gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
gpio_set_level(GPIO_NUM_2, 1);
```

### 2. APIs orientadas a características

Las APIs están diseñadas alrededor de las características del hardware en lugar de los registros. Por ejemplo, para configurar un temporizador:
```cpp
ledc_timer_config_t timer_conf = {
    .duty_resolution = LEDC_TIMER_10_BIT,
    .freq_hz = 5000,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .timer_num = LEDC_TIMER_0
};
ledc_timer_config(&timer_conf);
```

### 3. Sistema basado en eventos

Muchas partes del HAL utilizan un sistema de eventos para manejar interrupciones y notificaciones asíncronas. Esto facilita la programación de controladores que responden a eventos externos:
```cpp
// Configurar manejador de eventos WiFi
esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);

// Función manejadora
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    }
}
```

### Integración con FreeRTOS

El HAL de ESP32 está diseñado para trabajar con el sistema operativo en tiempo real FreeRTOS, que viene integrado en el ESP-IDF:
```cpp
// Crear una tarea
xTaskCreate(
    sensor_task,        // Función de la tarea
    "sensor_task",      // Nombre para depuración
    2048,               // Tamaño de stack (palabras)
    NULL,               // Parámetros
    5,                  // Prioridad
    NULL                // Handle (opcional)
);

// Usar primitivas de RTOS
xSemaphoreHandle mutex = xSemaphoreCreateMutex();
xSemaphoreTake(mutex, portMAX_DELAY);
// Acceder al recurso compartido
xSemaphoreGive(mutex);
```

## Ejemplos de uso del HAL

### GPIO
```cpp
// Configuración de un pin GPIO
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_4),  // Pin 4
    .mode = GPIO_MODE_INPUT,               // Modo entrada
    .pull_up_en = GPIO_PULLUP_ENABLE,      // Pull-up habilitado
    .pull_down_en = GPIO_PULLDOWN_DISABLE, // Pull-down deshabilitado
    .intr_type = GPIO_INTR_POSEDGE         // Interrupción en flanco ascendente
};
gpio_config(&io_conf);

// Configurar el manejador de interrupción
gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
gpio_isr_handler_add(GPIO_NUM_4, gpio_isr_handler, NULL);

// Manejador de interrupción
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // Código de manejo de interrupción
    // Normalmente se usa una cola para comunicar con tareas
}
```

### ADC
```cpp
// Configurar ADC
adc1_config_width(ADC_WIDTH_BIT_12);
adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

// Leer valor
int val = adc1_get_raw(ADC1_CHANNEL_0);
```

### WI-FI
```cpp
// Inicializar el subsistema WiFi
wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
esp_wifi_init(&cfg);
esp_wifi_set_mode(WIFI_MODE_STA);

// Configurar
wifi_config_t wifi_config = {
    .sta = {
        .ssid = "NOMBRE_RED",
        .password = "CONTRASEÑA",
    },
};
esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

// Iniciar
esp_wifi_start();
```

