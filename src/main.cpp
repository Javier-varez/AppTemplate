
#include "cortex_m_hal/systick.h"
#include "postform/rtt/transport.h"
#include "postform/serial_logger.h"
#include "systick_config.h"

int main() {
  Postform::Rtt::Transport transport;
  Postform::SerialLogger<Postform::Rtt::Transport> logger{&transport};

  SysTick& systick = SysTick::getInstance();

  systick.init(App::SYSTICK_CLK_HZ);

  logger.setLevel(Postform::LogLevel::DEBUG);

  while (true) {
    LOG_DEBUG(&logger, "I am alive!");
    systick.delay(SysTick::TICKS_PER_SECOND);
  }

  return 0;
}
