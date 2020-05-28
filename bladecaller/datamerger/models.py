from django.db import models
from django.contrib.gis.db import models as gis_models

from api.models import State

# Create your models here.

class VTDBlock(models.Model):
    state = models.ForeignKey(State, on_delete=models.CASCADE)
    geoid = models.CharField(max_length=255, unique=True)
    geometry = gis_models.GeometryField()

    land = models.FloatField()
    water = models.FloatField()

class TractBlock(models.Model):
    state = models.ForeignKey(State, on_delete=models.CASCADE)
    geometry = gis_models.GeometryField()

    land = models.FloatField()
    water = models.FloatField()

    totalPop = models.IntegerField(default=0)
    whitePop = models.IntegerField(default=0)
    blackPop = models.IntegerField(default=0)
    nativeAPop = models.IntegerField(default=0)
    asianPop = models.IntegerField(default=0)
    pacisPop = models.IntegerField(default=0)
    otherPop = models.IntegerField(default=0)
    multiPop = models.IntegerField(default=0)

class DistrictBlock(models.Model):
    state = models.ForeignKey(State, on_delete=models.CASCADE)
    district_id = models.IntegerField()
    geometry = gis_models.GeometryField()