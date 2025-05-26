# Muon Detection Experiment

This repository contains resources and documentation for a physics experiment aimed at detecting cosmic muons and measuring their lifetime using scintillators and Silicon Photomultipliers (SiPMs).

---

## 🕒 Muon Lifetime

## 🕒 Muon Lifetime

Muon lifetime measurement is a fundamental experiment in particle physics used to test the weak interaction and relativistic effects. Muons are elementary particles similar to electrons but with a mass about 207 times greater. They are unstable and decay primarily via:
`μ⁻ → e⁻ + νₑ + ν_μ`

The mean lifetime of a muon at rest is approximately **2.2 μs**, but due to relativistic time dilation, many survive long enough to reach the Earth's surface from the upper atmosphere.

In this experiment:
- A detection system composed of **three planes of plastic scintillators** was used.
- Cosmic muons pass through the first two planes and are **stopped in an iron slab** between the second and third planes.
- Once stopped, the muons decay into an electron and two neutrinos. The time between arrival and decay is measured.
- Signals from the scintillators were processed using **NIM and VME electronics** and digitized with a **Flash ADC** operating at 250 MS/s.

Data analysis involved extracting the time intervals between muon arrival and decay. These were used to build a decay time distribution and fitted with an exponential curve, yielding the measured lifetime:


This result is consistent with the standard value reported by the Particle Data Group (PDG), confirming the accuracy of the method.

![Muon Decay](images/fit_buono_1500bins.pdf)
*Image: Muon decay process (μ⁻ → e⁻ + ν̅ₑ + ν_μ)*

- Typical lifetime: ~2.2 microseconds at rest
- Due to time dilation, muons traveling near the speed of light can reach the Earth's surface

---

## 💡 Scintillators

Scintillators are materials that emit light (photons) when they are excited by ionizing radiation, such as when a muon passes through them. These materials are essential in detecting the passage of muons in our setup.

![Scintillator Material](images/fit_buono_1500bins.pdf)
*Image: Example of a plastic scintillator slab*

- Common materials: plastic or inorganic crystals (e.g., NaI(Tl))
- Emit photons in response to charged particles
- Coupled to light sensors (e.g., SiPMs) for readout

---

## 📷 Silicon Photomultipliers (SiPM)

SiPMs are highly sensitive light detectors used to detect the small flashes of light produced by scintillators. They are compact, solid-state devices with excellent timing resolution.

![SiPM](images/fit_buono_1500bins.pdf)
*Image: Silicon Photomultiplier device*

- Operate in Geiger mode to detect single photons
- Used for timing and energy measurements
- Ideal for portable or compact detector systems

---

## 📁 Contents

- `/src`: source code for data acquisition and analysis
- `/docs`: detailed documentation and references
- `/images`: high-resolution versions of figures and experimental setup

---

## 🧪 Authors & Contributions

This project is maintained by a group of physics students and educators passionate about particle detection. Contributions and feedback are welcome!

