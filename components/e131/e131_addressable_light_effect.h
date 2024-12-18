#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/addressable_light_effect.h"
#ifdef USE_NETWORK
namespace esphome {
namespace e131 {

class E131Component;
struct E131Packet;

enum E131LightChannels { E131_MONO = 1, E131_RGB = 3, E131_RGBW = 4, E131_UNIVERSE = 512 };

class E131AddressableLightEffect : public light::AddressableLightEffect {
 public:
  E131AddressableLightEffect(const std::string &name);

  void start() override;
  void stop() override;
  void apply(light::AddressableLight &it, const Color &current_color) override;

  int get_data_per_universe() const;
  int get_lights_per_universe() const;
  int get_first_universe() const;
  int get_last_universe() const;
  int get_universe_count() const;
  int get_first_channel() const;

  void set_first_universe(int universe) { this->first_universe_ = universe; }
  void set_first_channel(int channel) { this->first_channel_ = channel; }
  void set_channels(E131LightChannels channels) { this->channels_ = channels; }
  void set_e131(E131Component *e131) { this->e131_ = e131; }

 protected:
  bool process_(int universe, const E131Packet &packet);

  int first_universe_{0};
  int last_universe_{0};
  int first_channel_{0};
  E131LightChannels channels_{E131_RGB};
  E131Component *e131_{nullptr};

  friend class E131Component;
};

}  // namespace e131
}  // namespace esphome
#endif
