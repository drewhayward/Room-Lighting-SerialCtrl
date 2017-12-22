import { TestBed, inject } from '@angular/core/testing';

import { LightControllerService } from './light-controller.service';

describe('LightControllerService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [LightControllerService]
    });
  });

  it('should be created', inject([LightControllerService], (service: LightControllerService) => {
    expect(service).toBeTruthy();
  }));
});
